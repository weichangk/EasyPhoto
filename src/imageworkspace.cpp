#include "imageworkspace.h"
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPaintEvent>
#include <QFontMetrics>
#include <QtMath>

/*
┌─────────────────────────────────────────────────────┐
│              ImageWorkspace (QGraphicsView)         │
│  ┌───────────────────────────────────────────────┐  │
│  │          Viewport (视口窗口)                   │  │
│  │  ┌─────────────────────────────────────────┐  │  │
│  │  │    QGraphicsScene (场景/画布)           │  │  │
│  │  │  ┌───────────────────────────────────┐  │  │  │
│  │  │  │  QGraphicsPixmapItem (图片项)     │  │  │  │
│  │  │  │  ┌─────────────────────────────┐  │  │  │  │
│  │  │  │  │   QPixmap (实际图片数据)    │  │  │  │  │
│  │  │  │  └─────────────────────────────┘  │  │  │  │
│  │  │  └───────────────────────────────────┘  │  │  │
│  │  └─────────────────────────────────────────┘  │  │
│  │                                                │  │
│  │  + m_cropOverlay (视口坐标的裁剪框)           │  │
│  └───────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────┘

变换关系: Viewport ←→ Scene ←→ Item (PixmapItem)
 */

// ==================== ImageWorkspace 实现 ====================
ImageWorkspace::ImageWorkspace(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_pixmapItem(new QGraphicsPixmapItem()),
    m_scaleFactor(1.0),
    m_isPanning(false),
    m_mode(ModeNone),
    m_cropAspectMode(CropAspectFree),
    m_cropOverlay(),
    m_overlayHandle(HandleNone),
    m_draggingOverlay(false) {
    setObjectName("ImageWorkspace");
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(m_scene);
    m_scene->addItem(m_pixmapItem);

    // // 设置场景背景色
    // m_scene->setBackgroundBrush(QBrush(Qt::red));
    
    // // 设置视口背景色
    // setBackgroundBrush(QBrush(Qt::blue));

    setDragMode(QGraphicsView::NoDrag);
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void ImageWorkspace::loadImage(const QString &filePath) {
    QPixmap pixmap(filePath);
    if (pixmap.isNull()) {
        qDebug() << "Failed to load image!";
        return;
    }
    m_pixmapItem->setPixmap(pixmap);
    emit imageSizeChanged(pixmap.size()); // 发送图片实际大小信号
    if (m_mode == ModeResize) {
        // Resize 模式：支持固定尺寸或 QSize(0,0) 自动使用图片尺寸
        initResizeCanvas();
        resetTransform(); // 视图变换归零，保持 1:1，图片已缩放适配
        updateScaleFactor();
    } else {
        // 普通/裁剪模式行为：sceneRect = 图片尺寸 + 自适应视图
        m_scene->setSceneRect(pixmap.rect());
        setFitView();
    }
}

void ImageWorkspace::setFitView() {
    if (m_mode == ModeResize) {
        // Resize 模式：适配整个画布（sceneRect），而不是图片
        fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
    } else {
        fitInView(m_pixmapItem, Qt::KeepAspectRatio);
    }
    updateScaleFactor(); // 计算fitInView后的实际缩放比例
}

void ImageWorkspace::resetView() {
    resetTransform();
    m_scaleFactor = 1.0;
    emit scaleFactorChanged(m_scaleFactor);
    viewport()->update();
}

void ImageWorkspace::zoomIn() {
    // Resize 模式与普通模式统一：缩放视图（场景），而不是缩放图片项
    scale(1.01, 1.01);  // 每次放大1%
    updateScaleFactor();
}

void ImageWorkspace::zoomOut() {
    scale(1/1.01, 1/1.01);
    updateScaleFactor();
}

void ImageWorkspace::zoomToPercent(double percent) {
    if (percent <= 0.0) return; // 无效输入

    qreal target = percent / 100.0; // percent -> 比例因子

    // 限制到合理范围，避免变得过小或过大（可根据需要调整）
    target = qBound<qreal>(0.01, target, 20.0);

    // 如果在裁剪模式下，确保不小于使图片覆盖裁剪框的最小缩放
    if (m_mode == ModeCrop && !m_cropOverlay.isNull()) {
        qreal minScale = getMinScaleForCropOverlay();
        if (minScale > 0.0 && target < minScale) {
            target = minScale;
        }
    }

    // 计算相对缩放因子并应用
    qreal factor = target / m_scaleFactor;
    scale(factor, factor);
    updateScaleFactor();
}

void ImageWorkspace::updateScaleFactor() {
    // 计算当前变换矩阵的实际缩放比例
    QTransform t = transform();
    m_scaleFactor = qSqrt(t.m11() * t.m11() + t.m12() * t.m12());
    emit scaleFactorChanged(m_scaleFactor);
    viewport()->update(); // 触发重绘以更新缩放显示
}

void ImageWorkspace::wheelEvent(QWheelEvent *event) {
    if (m_mode == ModeCrop && !m_cropOverlay.isNull()) {
        // ModeCrop 模式下缩小时检查限制：图片投影不能缩到选区边界以内
        if (event->angleDelta().y() < 0) {
            // 先执行缩小
            qreal oldScale = m_scaleFactor;
            scale(1 / 1.01, 1 / 1.01);
            m_scaleFactor /= 1.01;
            
            // 检查缩小后图片投影是否仍包含选区
            QRect newImageVp = overlaySceneRectToViewport(m_pixmapItem->sceneBoundingRect());
            
            if (!newImageVp.contains(m_cropOverlay)) {
                // 缩小后图片不能完全包含选区，回退缩放
                resetTransform();
                scale(oldScale, oldScale);
                m_scaleFactor = oldScale;
                emit scaleFactorChanged(m_scaleFactor);
                viewport()->update();
                return;
            }
            
            // 缩放有效，发射信号
            emit scaleFactorChanged(m_scaleFactor);
            viewport()->update();
        } else {
            zoomIn();
        }
    } else {
        if (event->angleDelta().y() > 0) {
            zoomIn();
        } else {
            zoomOut();
        }
    }
}

void ImageWorkspace::setWorkspaceMode(WorkspaceMode mode) {
    if (m_mode == mode) return;
    
    // 保存当前模式的图片状态
    if (m_mode == ModeResize) {
        saveImageItemState(m_resizeModeState);
    } else {
        saveImageItemState(m_cropModeState);
    }
    
    // 保存/清理当前模式资源
    if (m_mode == ModeCrop) {
        // 保存选框的场景坐标（用于后续恢复）
        if (!m_cropOverlay.isNull()) {
            m_savedCropOverlayScene = overlayViewportRectToScene(m_cropOverlay);
        }
        m_cropOverlay = QRect();
    }
    
    m_mode = mode;
    
    // 初始化新模式并恢复状态
    if (m_mode == ModeCrop || m_mode == ModeNone) {
        // 恢复到 Crop/None 模式：场景 = 图片大小，图片项在原点无缩放
        if (m_pixmapItem && !m_pixmapItem->pixmap().isNull()) {
            m_scene->setSceneRect(m_pixmapItem->pixmap().rect());
            resetImageItemToOriginal();
        }
        setFitView(); // 先设置视图变换
        
        if (m_mode == ModeCrop) {
            // 如果有保存的选框，恢复它；否则初始化新选框
            if (!m_savedCropOverlayScene.isNull()) {
                // 在视图变换确定后，将场景坐标转换为视口坐标
                m_cropOverlay = overlaySceneRectToViewport(m_savedCropOverlayScene);
                // 确保恢复的选框在图片范围内
                clampOverlayToImage(m_cropOverlay, true);
            } else {
                initOverlayFromVisibleImage();
            }
        }
    } else if (m_mode == ModeResize) {
        initResizeCanvas();
        setFitView(); // 适配整个画布
    }
    
    viewport()->update();
    emit modeChanged(m_mode);
}

void ImageWorkspace::setCropAspectRatioMode(CropAspectRatioMode mode) {
    if (m_cropAspectMode == mode) return;
    m_cropAspectMode = mode;
    
    // 如果当前在裁剪模式，重新初始化选区为居中且最大尺寸
    if (m_mode == ModeCrop && m_pixmapItem && !m_pixmapItem->pixmap().isNull()) {
        // 获取图片在视口中的投影区域
        QRect imageVp = overlaySceneRectToViewport(m_pixmapItem->sceneBoundingRect());
        if (imageVp.isEmpty()) return;
        
        qreal aspectRatio = getAspectRatio();
        
        if (aspectRatio > 0.0) {
            // 按比例模式：计算在图片范围内能容纳的最大选区
            int maxWidth = imageVp.width();
            int maxHeight = imageVp.height();
            
            int fitWidth = maxWidth;
            int fitHeight = qRound(fitWidth / aspectRatio);
            
            if (fitHeight > maxHeight) {
                fitHeight = maxHeight;
                fitWidth = qRound(fitHeight * aspectRatio);
            }
            
            // 创建居中的选区
            m_cropOverlay = QRect(0, 0, fitWidth, fitHeight);
            m_cropOverlay.moveCenter(imageVp.center());
        } else {
            // 自由模式：铺满整个图片
            m_cropOverlay = imageVp;
        }
        
        viewport()->update();
        emit cropRectChanged(getCropRect());
    }
}

void ImageWorkspace::resetCropRect() {
    if (m_mode == ModeCrop) {
        initOverlayFromVisibleImage();
        viewport()->update();
    }
}

QRectF ImageWorkspace::getCropRect() const {
    if (m_mode == ModeCrop) {
        if (m_cropOverlay.isNull()) return QRectF();
        return overlayViewportRectToScene(m_cropOverlay);
    }
    return QRectF();
}

QRect ImageWorkspace::getCropRectInImage() const {
    if (m_pixmapItem->pixmap().isNull()) return QRect();
    QRectF sceneRect = getCropRect();
    if (sceneRect.isNull()) return QRect();
    QRectF itemRect = m_pixmapItem->mapRectFromScene(sceneRect);
    return itemRect.toRect();
}

void ImageWorkspace::clearCropRect() {
    if (m_mode == ModeCrop) {
        m_cropOverlay = QRect();
    }
    viewport()->update();
}

QPixmap ImageWorkspace::getCroppedImage() const {
    if (m_mode==ModeNone || m_pixmapItem->pixmap().isNull()) return QPixmap();
    QRect cropRect = getCropRectInImage();
    if (cropRect.isEmpty()) return QPixmap();
    return m_pixmapItem->pixmap().copy(cropRect.intersected(m_pixmapItem->pixmap().rect()));
}

void ImageWorkspace::mousePressEvent(QMouseEvent *event) {
    if (event->button()==Qt::LeftButton) {
        if (m_mode==ModeCrop) {
            m_overlayHandle = hitTestOverlayHandle(event->pos());
            if (m_overlayHandle!=HandleNone) {
                // 角/边缩放 或 中心移动
                m_draggingOverlay=true;
                m_dragStartPos=event->pos();
                m_dragStartOverlay=m_cropOverlay;
                updateCursorForHandle(m_overlayHandle);
                event->accept();
                return;
            }
            // 选区外：进入图片平移
            m_isPanning=true; m_lastMousePos=event->pos(); setCursor(Qt::ClosedHandCursor); event->accept(); return;
        }
        if (m_mode==ModeResize) {
            // 判断是否点击在图片上，准备拖动图片
            if (m_pixmapItem && !m_pixmapItem->pixmap().isNull()) {
                QPointF scenePos = mapToScene(event->pos());
                if (m_pixmapItem->contains(m_pixmapItem->mapFromScene(scenePos))) {
                    m_isImageDragging = true;
                    m_imageDragStartPos = event->pos();
                    m_imageItemStartPos = m_pixmapItem->pos();
                    setCursor(Qt::ClosedHandCursor);
                    event->accept();
                    return;
                }
            }
            // 未点中图片：不允许平移视图，直接忽略让父级处理（或保持静止）
            event->ignore();
            return;
        }
        // 进入平移（非 Resize 模式）
        m_isPanning=true; m_lastMousePos=event->pos(); setCursor(Qt::ClosedHandCursor); event->accept(); return;
    }
    QGraphicsView::mousePressEvent(event);
}

void ImageWorkspace::mouseMoveEvent(QMouseEvent *event) {
    if (m_mode==ModeCrop && m_draggingOverlay) {
        QPoint delta = event->pos() - m_dragStartPos;
        QRect r = m_dragStartOverlay;
        
        switch (m_overlayHandle) {
            case HandleTopLeft: r.setTopLeft((m_dragStartOverlay.topLeft()+delta)); break;
            case HandleTopRight: r.setTopRight((m_dragStartOverlay.topRight()+delta)); break;
            case HandleBottomLeft: r.setBottomLeft((m_dragStartOverlay.bottomLeft()+delta)); break;
            case HandleBottomRight: r.setBottomRight((m_dragStartOverlay.bottomRight()+delta)); break;
            case HandleTop: r.setTop(m_dragStartOverlay.top()+delta.y()); break;
            case HandleBottom: r.setBottom(m_dragStartOverlay.bottom()+delta.y()); break;
            case HandleLeft: r.setLeft(m_dragStartOverlay.left()+delta.x()); break;
            case HandleRight: r.setRight(m_dragStartOverlay.right()+delta.x()); break;
            case HandleCenter: r.translate(delta); break;
            default: break;
        }
        // 归一化并最小尺寸（中心拖动不需要归一化改变形状，只是平移）
        if (m_overlayHandle != HandleCenter) {
            r = r.normalized();
            if (r.width() < 20) r.setWidth(20);
            if (r.height() < 20) r.setHeight(20);
            
            // 获取图片投影区域
            QRect imageVp = overlaySceneRectToViewport(m_pixmapItem->sceneBoundingRect());
            
            // 应用比例约束（如果不是自由模式）
            qreal aspectRatio = getAspectRatio();
            if (aspectRatio > 0.0 && !imageVp.isEmpty()) {
                // 应用比例约束
                r = constrainToAspectRatio(r, m_overlayHandle);
                
                // 检查是否超出图片边界（任意一条边超出都算超出）
                if (r.left() < imageVp.left() || r.top() < imageVp.top() ||
                    r.right() > imageVp.right() || r.bottom() > imageVp.bottom()) {
                    
                    // 计算在不超出边界的情况下，能容纳的最大尺寸（保持比例）
                    int maxWidth = imageVp.width();
                    int maxHeight = imageVp.height();
                    
                    // 从拖动起始位置的对应锚点开始计算可用空间
                    int availableWidth = maxWidth;
                    int availableHeight = maxHeight;
                    
                    // 根据句柄确定可用空间
                    switch (m_overlayHandle) {
                        case HandleTopLeft:
                            availableWidth = m_dragStartOverlay.right() - imageVp.left();
                            availableHeight = m_dragStartOverlay.bottom() - imageVp.top();
                            break;
                        case HandleTopRight:
                            availableWidth = imageVp.right() - m_dragStartOverlay.left();
                            availableHeight = m_dragStartOverlay.bottom() - imageVp.top();
                            break;
                        case HandleBottomLeft:
                            availableWidth = m_dragStartOverlay.right() - imageVp.left();
                            availableHeight = imageVp.bottom() - m_dragStartOverlay.top();
                            break;
                        case HandleBottomRight:
                            availableWidth = imageVp.right() - m_dragStartOverlay.left();
                            availableHeight = imageVp.bottom() - m_dragStartOverlay.top();
                            break;
                        case HandleTop:
                        case HandleBottom:
                            availableHeight = (m_overlayHandle == HandleTop) ? 
                                (m_dragStartOverlay.bottom() - imageVp.top()) : 
                                (imageVp.bottom() - m_dragStartOverlay.top());
                            // 宽度需要居中，所以可用空间受限
                            availableWidth = qMin(
                                (m_dragStartOverlay.center().x() - imageVp.left()) * 2,
                                (imageVp.right() - m_dragStartOverlay.center().x()) * 2
                            );
                            break;
                        case HandleLeft:
                        case HandleRight:
                            availableWidth = (m_overlayHandle == HandleLeft) ? 
                                (m_dragStartOverlay.right() - imageVp.left()) : 
                                (imageVp.right() - m_dragStartOverlay.left());
                            // 高度需要居中，所以可用空间受限
                            availableHeight = qMin(
                                (m_dragStartOverlay.center().y() - imageVp.top()) * 2,
                                (imageVp.bottom() - m_dragStartOverlay.center().y()) * 2
                            );
                            break;
                        default:
                            break;
                    }
                    
                    // 按比例计算能容纳的最大尺寸
                    int fitWidth = availableWidth;
                    int fitHeight = qRound(fitWidth / aspectRatio);
                    
                    if (fitHeight > availableHeight) {
                        fitHeight = availableHeight;
                        fitWidth = qRound(fitHeight * aspectRatio);
                    }
                    
                    // 设置限制后的尺寸
                    r.setSize(QSize(fitWidth, fitHeight));
                    
                    // 根据句柄重新定位
                    switch (m_overlayHandle) {
                        case HandleTopLeft:     r.moveBottomRight(m_dragStartOverlay.bottomRight()); break;
                        case HandleTopRight:    r.moveBottomLeft(m_dragStartOverlay.bottomLeft()); break;
                        case HandleBottomLeft:  r.moveTopRight(m_dragStartOverlay.topRight()); break;
                        case HandleBottomRight: r.moveTopLeft(m_dragStartOverlay.topLeft()); break;
                        case HandleTop:         r.moveBottom(m_dragStartOverlay.bottom()); 
                                                r.moveCenter(QPoint(m_dragStartOverlay.center().x(), r.center().y())); 
                                                break;
                        case HandleBottom:      r.moveTop(m_dragStartOverlay.top()); 
                                                r.moveCenter(QPoint(m_dragStartOverlay.center().x(), r.center().y())); 
                                                break;
                        case HandleLeft:        r.moveRight(m_dragStartOverlay.right()); 
                                                r.moveCenter(QPoint(r.center().x(), m_dragStartOverlay.center().y())); 
                                                break;
                        case HandleRight:       r.moveLeft(m_dragStartOverlay.left()); 
                                                r.moveCenter(QPoint(r.center().x(), m_dragStartOverlay.center().y())); 
                                                break;
                        default:
                            break;
                    }
                }
                
                // 最终确保在图片范围内
                clampOverlayToImage(r, false);
            } else {
                // 自由模式：直接限制边界
                clampOverlayToImage(r, false);
            }
        } else {
            // 移动时：保持大小不变
            clampOverlayToImage(r, true);
        }
        m_cropOverlay = r;
        
        viewport()->update();
        event->accept();
        return;
    }
    if (m_mode==ModeResize && m_isImageDragging) {
        QPoint delta = event->pos() - m_imageDragStartPos;
        QPointF newPos = m_imageItemStartPos + QPointF(delta.x(), delta.y());
        m_pixmapItem->setPos(newPos);
        clampImageInsideCanvas();
        viewport()->update();
        event->accept();
        return;
    }
    if (m_isPanning) {
        QPointF delta = mapToScene(event->pos()) - mapToScene(m_lastMousePos);
        translate(delta.x(), delta.y());
        m_lastMousePos = event->pos();
        viewport()->update();
        event->accept();
        return;
    }
    if (m_mode==ModeCrop) { updateCursorForHandle(hitTestOverlayHandle(event->pos())); }
    QGraphicsView::mouseMoveEvent(event);
}

void ImageWorkspace::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button()==Qt::LeftButton) {
        if (m_mode==ModeCrop && m_draggingOverlay) {
            m_draggingOverlay=false; 
            m_overlayHandle=HandleNone; 
            updateCursorForHandle(hitTestOverlayHandle(event->pos())); 
            emit cropRectChanged(getCropRect());
            event->accept(); 
            return; 
        }
        if (m_mode==ModeResize && m_isImageDragging) {
            m_isImageDragging = false;
            setCursor(Qt::ArrowCursor);
            event->accept();
            return;
        }
        if (m_isPanning) { m_isPanning=false; setCursor(Qt::ArrowCursor); event->accept(); return; }
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void ImageWorkspace::paintEvent(QPaintEvent *event) {
    QGraphicsView::paintEvent(event);
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 绘制场景边框（画布边框）
    if (m_pixmapItem && !m_pixmapItem->pixmap().isNull()) {
        QRect imageVp = overlaySceneRectToViewport(m_pixmapItem->sceneBoundingRect());
        if (!imageVp.isEmpty()) {
            painter.setPen(QPen(QColor(150, 150, 150), 1, Qt::DashLine));
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(imageVp);
        }
    }
    
    // 绘制裁剪覆盖
    if (m_mode==ModeCrop && !m_cropOverlay.isNull()) {
        paintOverlay(painter);
    }
    // Resize 模式下绘制固定画布边界（sceneRect）
    if (m_mode==ModeResize) {
        QRectF sceneR = m_scene->sceneRect();
        QRect canvasVp = overlaySceneRectToViewport(sceneR);
        painter.setPen(QPen(QColor(200,200,200), 2));
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(canvasVp);
    }
}

void ImageWorkspace::resizeEvent(QResizeEvent *event) {
    // ModeCrop 模式下，保存选区在图片中的相对位置和大小（比例）
    QRectF relativeRect; // 相对于图片的归一化矩形 [0.0, 1.0]
    bool hadCropOverlay = false;
    
    if (m_mode == ModeCrop && !m_cropOverlay.isNull() && m_pixmapItem && !m_pixmapItem->pixmap().isNull()) {
        hadCropOverlay = true;
        
        // 将视口选区转换为场景坐标
        QRectF overlaySceneRect = overlayViewportRectToScene(m_cropOverlay);
        
        // 获取图片在场景中的矩形
        QRectF imageSceneRect = m_pixmapItem->sceneBoundingRect();
        
        // 计算选区相对于图片的归一化矩形（0.0 ~ 1.0）
        if (!imageSceneRect.isEmpty()) {
            qreal relLeft = (overlaySceneRect.left() - imageSceneRect.left()) / imageSceneRect.width();
            qreal relTop = (overlaySceneRect.top() - imageSceneRect.top()) / imageSceneRect.height();
            qreal relWidth = overlaySceneRect.width() / imageSceneRect.width();
            qreal relHeight = overlaySceneRect.height() / imageSceneRect.height();
            
            relativeRect = QRectF(relLeft, relTop, relWidth, relHeight);
        }
    }
    
    QGraphicsView::resizeEvent(event);
    
    // 窗口改变后，根据保存的相对位置恢复选区
    if (hadCropOverlay && !relativeRect.isNull() && m_pixmapItem && !m_pixmapItem->pixmap().isNull()) {
        // 获取新的图片在场景中的矩形
        QRectF imageSceneRect = m_pixmapItem->sceneBoundingRect();
        
        if (!imageSceneRect.isEmpty()) {
            // 根据归一化比例计算新的选区场景坐标
            qreal newLeft = imageSceneRect.left() + relativeRect.left() * imageSceneRect.width();
            qreal newTop = imageSceneRect.top() + relativeRect.top() * imageSceneRect.height();
            qreal newWidth = relativeRect.width() * imageSceneRect.width();
            qreal newHeight = relativeRect.height() * imageSceneRect.height();
            
            QRectF newOverlayScene(newLeft, newTop, newWidth, newHeight);
            
            // 转换回视口坐标
            m_cropOverlay = overlaySceneRectToViewport(newOverlayScene);
            
            // 约束选区在图片范围内
            clampOverlayToImage(m_cropOverlay);
            
            // 触发重绘
            viewport()->update();
        }
    }
}

// ==================== 新裁剪覆盖实现 ====================
QRectF ImageWorkspace::overlayViewportRectToScene(const QRect &vpRect) const {
    if (vpRect.isNull()) return QRectF();
    QPointF tlScene = mapToScene(vpRect.topLeft());
    QPointF brScene = mapToScene(vpRect.bottomRight());
    return QRectF(tlScene, brScene).normalized();
}

QRect ImageWorkspace::overlaySceneRectToViewport(const QRectF &sceneRect) const {
    if (sceneRect.isNull()) return QRect();
    QPoint tl = mapFromScene(sceneRect.topLeft());
    QPoint br = mapFromScene(sceneRect.bottomRight());
    return QRect(tl, br).normalized();
}

void ImageWorkspace::initOverlayFromVisibleImage() {
    if (m_pixmapItem->pixmap().isNull()) { m_cropOverlay = QRect(); return; }
    // 可见图像区域：当前图片在视口的投影
    QRect imageVp = overlaySceneRectToViewport(m_pixmapItem->sceneBoundingRect());
    if (imageVp.isEmpty()) { m_cropOverlay = QRect(); return; }
    // 初始选区铺满整个可见图片
    m_cropOverlay = imageVp;
    emit cropRectChanged(getCropRect());
}

void ImageWorkspace::clampOverlayToImage(QRect &overlay, bool preserveSize) {
    if (overlay.isNull()) return;
    QRect imageVp = overlaySceneRectToViewport(m_pixmapItem->sceneBoundingRect());
    if (imageVp.isEmpty()) { overlay = QRect(); return; }
    
    if (preserveSize) {
        // 移动模式：保持大小不变，只调整位置
        int width = overlay.width();
        int height = overlay.height();
        int newX = overlay.x();
        int newY = overlay.y();
        
        // 限制 X 坐标
        if (newX < imageVp.left()) {
            newX = imageVp.left();
        } else if (newX + width > imageVp.right()) {
            newX = imageVp.right() - width;
        }
        
        // 限制 Y 坐标
        if (newY < imageVp.top()) {
            newY = imageVp.top();
        } else if (newY + height > imageVp.bottom()) {
            newY = imageVp.bottom() - height;
        }
        
        overlay = QRect(newX, newY, width, height);
    } else {
        // 缩放模式：限制边界但允许改变大小
        if (overlay.left() < imageVp.left()) overlay.setLeft(imageVp.left());
        if (overlay.top() < imageVp.top()) overlay.setTop(imageVp.top());
        if (overlay.right() > imageVp.right()) overlay.setRight(imageVp.right());
        if (overlay.bottom() > imageVp.bottom()) overlay.setBottom(imageVp.bottom());
    }
}


ImageWorkspace::OverlayHandle ImageWorkspace::hitTestOverlayHandle(const QPoint &vpPos) const {
    if (m_mode!=ModeCrop || m_cropOverlay.isNull()) return HandleNone;
    
    const int hs = m_handleVisualSize;
    const qreal anchorRadius = 12.0;
    
    auto rectAt=[&](int x,int y){return QRect(x-hs/2,y-hs/2,hs,hs);};
    
    // 四个角控制点
    if (rectAt(m_cropOverlay.left(), m_cropOverlay.top()).contains(vpPos)) return HandleTopLeft;
    if (rectAt(m_cropOverlay.right(), m_cropOverlay.top()).contains(vpPos)) return HandleTopRight;
    if (rectAt(m_cropOverlay.left(), m_cropOverlay.bottom()).contains(vpPos)) return HandleBottomLeft;
    if (rectAt(m_cropOverlay.right(), m_cropOverlay.bottom()).contains(vpPos)) return HandleBottomRight;
    
    // 四条边中点控制点
    if (rectAt(m_cropOverlay.center().x(), m_cropOverlay.top()).contains(vpPos)) return HandleTop;
    if (rectAt(m_cropOverlay.center().x(), m_cropOverlay.bottom()).contains(vpPos)) return HandleBottom;
    if (rectAt(m_cropOverlay.left(), m_cropOverlay.center().y()).contains(vpPos)) return HandleLeft;
    if (rectAt(m_cropOverlay.right(), m_cropOverlay.center().y()).contains(vpPos)) return HandleRight;
    
    // 中心锚点（圆形区域）
    QPointF center = m_cropOverlay.center();
    qreal distToCenter = QLineF(center, vpPos).length();
    if (distToCenter <= anchorRadius) {
        return HandleCenter;
    }
    
    // 其他区域返回 None，实现鼠标穿透
    return HandleNone;
}

qreal ImageWorkspace::getMinScaleForCropOverlay() const {
    if (m_pixmapItem->pixmap().isNull() || m_cropOverlay.isNull()) {
        return 0.0;
    }
    
    // 获取图片原始尺寸
    QSize imgSize = m_pixmapItem->pixmap().size();
    
    // 选区在视口中的尺寸（像素）
    int cropWidth = m_cropOverlay.width();
    int cropHeight = m_cropOverlay.height();
    
    // 计算需要的最小缩放：图片在该缩放下的视口投影必须至少等于选区大小
    // 在缩放 s 下，图片宽度在视口的投影 = imgSize.width() * s
    // 需要：imgSize.width() * s >= cropWidth
    // 所以：s >= cropWidth / imgSize.width()
    qreal minScaleW = (qreal)cropWidth / (qreal)imgSize.width();
    qreal minScaleH = (qreal)cropHeight / (qreal)imgSize.height();
    
    // 取较大值，确保两个维度都能覆盖选区
    // 加一个小的容差避免浮点误差
    return qMax(minScaleW, minScaleH) * 1.001;
}

void ImageWorkspace::updateCursorForHandle(OverlayHandle h) {
    switch (h) {
        case HandleTopLeft: case HandleBottomRight: setCursor(Qt::SizeFDiagCursor); break;
        case HandleTopRight: case HandleBottomLeft: setCursor(Qt::SizeBDiagCursor); break;
        case HandleTop: case HandleBottom: setCursor(Qt::SizeVerCursor); break;
        case HandleLeft: case HandleRight: setCursor(Qt::SizeHorCursor); break;
        case HandleCenter: setCursor(Qt::SizeAllCursor); break;
        default: setCursor(Qt::ArrowCursor); break; // 选区外部/无锚点
    }
}

void ImageWorkspace::paintOverlay(QPainter &painter) {
    if (m_cropOverlay.isNull()) return;
    
    // 获取图片在视口中的投影区域
    QRect imageVp = overlaySceneRectToViewport(m_pixmapItem->sceneBoundingRect());
    if (imageVp.isEmpty()) return;
    
    // 半透明遮罩：只覆盖图片区域，不覆盖整个视口
    QPainterPath path; 
    path.addRect(imageVp);  // 图片区域
    path.addRect(m_cropOverlay);  // 选区
    painter.fillPath(path, QColor(0,0,0,120));
    
    // 边框
    painter.setPen(QPen(Qt::white,2)); painter.setBrush(Qt::NoBrush); painter.drawRect(m_cropOverlay);
    // 九宫格
    painter.setPen(QPen(Qt::white,1,Qt::DashLine));
    int x1=m_cropOverlay.left()+m_cropOverlay.width()/3; int x2=m_cropOverlay.left()+m_cropOverlay.width()*2/3;
    int y1=m_cropOverlay.top()+m_cropOverlay.height()/3; int y2=m_cropOverlay.top()+m_cropOverlay.height()*2/3;
    painter.drawLine(QPoint(x1,m_cropOverlay.top()), QPoint(x1,m_cropOverlay.bottom()));
    painter.drawLine(QPoint(x2,m_cropOverlay.top()), QPoint(x2,m_cropOverlay.bottom()));
    painter.drawLine(QPoint(m_cropOverlay.left(), y1), QPoint(m_cropOverlay.right(), y1));
    painter.drawLine(QPoint(m_cropOverlay.left(), y2), QPoint(m_cropOverlay.right(), y2));
    
    // 绘制控制点和锚点（与 Resize 模式一致）
    painter.setPen(Qt::NoPen); painter.setBrush(Qt::white);
    int hs=m_handleVisualSize; 
    auto drawHandle=[&](const QPoint&p){ QRect r(p.x()-hs/2,p.y()-hs/2,hs,hs); painter.drawRect(r); };
    
    // 四个角控制点
    drawHandle(m_cropOverlay.topLeft()); 
    drawHandle(m_cropOverlay.topRight());
    drawHandle(m_cropOverlay.bottomLeft()); 
    drawHandle(m_cropOverlay.bottomRight());
    
    // 四条边中点控制点
    drawHandle(QPoint(m_cropOverlay.center().x(), m_cropOverlay.top()));      // Top
    drawHandle(QPoint(m_cropOverlay.center().x(), m_cropOverlay.bottom()));   // Bottom
    drawHandle(QPoint(m_cropOverlay.left(), m_cropOverlay.center().y()));     // Left
    drawHandle(QPoint(m_cropOverlay.right(), m_cropOverlay.center().y()));    // Right
    
    // 中心锚点（圆形，用于移动选区）
    QPointF center = m_cropOverlay.center();
    qreal anchorRadius = 12.0;
    
    // 外圈(白色描边)
    painter.setPen(QPen(QColor(255, 255, 255), 2));
    painter.setBrush(QColor(100, 100, 100, 180));
    painter.drawEllipse(center, anchorRadius, anchorRadius);
    
    // 内圈(更小的白色实心圆)
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255));
    painter.drawEllipse(center, anchorRadius * 0.4, anchorRadius * 0.4);
    
    // 尺寸标签
    QString sizeText = QString("%1 × %2").arg(getCropRectInImage().width()).arg(getCropRectInImage().height());
    QFont font; font.setPixelSize(12); painter.setFont(font); QFontMetrics fm(font); QRect tr=fm.boundingRect(sizeText); int pad=4;
    QRect bg(m_cropOverlay.center().x()-tr.width()/2 - pad, m_cropOverlay.bottom()-tr.height()-pad-6, tr.width()+pad*2, tr.height()+pad);
    painter.setBrush(QColor(0,0,0,160)); painter.setPen(Qt::NoPen); painter.drawRoundedRect(bg,3,3);
    painter.setPen(Qt::white); painter.drawText(bg, Qt::AlignCenter, sizeText);
}

// ==================== 裁剪比例辅助函数 ====================
qreal ImageWorkspace::getAspectRatio() const {
    switch (m_cropAspectMode) {
        case CropAspectFree:      return 0.0;  // 0 表示自由比例
        case CropAspectOriginal:  // 原始图片比例
            if (m_pixmapItem && !m_pixmapItem->pixmap().isNull()) {
                QSize imgSize = m_pixmapItem->pixmap().size();
                return (qreal)imgSize.width() / (qreal)imgSize.height();
            }
            return 1.0;
        case CropAspectSquare:    return 1.0;      // 1:1
        case CropAspect16_9:      return 16.0/9.0; // 16:9
        case CropAspect9_16:      return 9.0/16.0; // 9:16
        case CropAspect4_5:       return 4.0/5.0;  // 4:5
        case CropAspect5_4:       return 5.0/4.0;  // 5:4
        case CropAspect3_4:       return 3.0/4.0;  // 3:4
        case CropAspect4_3:       return 4.0/3.0;  // 4:3
        case CropAspect2_3:       return 2.0/3.0;  // 2:3
        case CropAspect3_2:       return 3.0/2.0;  // 3:2
        case CropAspect5_7:       return 5.0/7.0;  // 5:7
        case CropAspect7_5:       return 7.0/5.0;  // 7:5
        case CropAspect1_2:       return 1.0/2.0;  // 1:2
        case CropAspect2_1:       return 2.0/1.0;  // 2:1
        default:                  return 0.0;
    }
}

QRect ImageWorkspace::constrainToAspectRatio(const QRect &rect, OverlayHandle handle) const {
    qreal aspectRatio = getAspectRatio();
    
    // 自由模式，不约束比例
    if (aspectRatio <= 0.0) {
        return rect;
    }
    
    QRect result = rect.normalized();
    int width = result.width();
    int height = result.height();
    
    // 根据拖动的句柄决定如何调整，并保持对应的锚点不变
    switch (handle) {
        case HandleTopLeft: {
            // 左上角：保持右下角不变
            QPoint anchor = result.bottomRight();
            int newHeight = qRound(width / aspectRatio);
            result.setHeight(newHeight);
            result.moveBottomRight(anchor);
            break;
        }
        case HandleTopRight: {
            // 右上角：保持左下角不变
            QPoint anchor = result.bottomLeft();
            int newHeight = qRound(width / aspectRatio);
            result.setHeight(newHeight);
            result.moveBottomLeft(anchor);
            break;
        }
        case HandleBottomLeft: {
            // 左下角：保持右上角不变
            QPoint anchor = result.topRight();
            int newHeight = qRound(width / aspectRatio);
            result.setHeight(newHeight);
            result.moveTopRight(anchor);
            break;
        }
        case HandleBottomRight: {
            // 右下角：保持左上角不变
            QPoint anchor = result.topLeft();
            int newHeight = qRound(width / aspectRatio);
            result.setHeight(newHeight);
            result.moveTopLeft(anchor);
            break;
        }
        case HandleTop: {
            // 顶边：保持底边不变，调整宽度
            int bottom = result.bottom();
            int newWidth = qRound(height * aspectRatio);
            int centerX = result.center().x();
            result.setWidth(newWidth);
            result.setBottom(bottom);
            result.moveCenter(QPoint(centerX, result.center().y()));
            break;
        }
        case HandleBottom: {
            // 底边：保持顶边不变，调整宽度
            int top = result.top();
            int newWidth = qRound(height * aspectRatio);
            int centerX = result.center().x();
            result.setWidth(newWidth);
            result.setTop(top);
            result.moveCenter(QPoint(centerX, result.center().y()));
            break;
        }
        case HandleLeft: {
            // 左边：保持右边不变，调整高度
            int right = result.right();
            int newHeight = qRound(width / aspectRatio);
            int centerY = result.center().y();
            result.setHeight(newHeight);
            result.setRight(right);
            result.moveCenter(QPoint(result.center().x(), centerY));
            break;
        }
        case HandleRight: {
            // 右边：保持左边不变，调整高度
            int left = result.left();
            int newHeight = qRound(width / aspectRatio);
            int centerY = result.center().y();
            result.setHeight(newHeight);
            result.setLeft(left);
            result.moveCenter(QPoint(result.center().x(), centerY));
            break;
        }
        case HandleCenter:
            // 中心移动：保持原有尺寸和比例
            break;
        default:
            break;
    }
    
    return result;
}

// ==================== Resize 模式辅助实现 ====================
void ImageWorkspace::setResizeCanvasSize(const QSize &size) {
    // 允许 QSize(0,0) 表示使用图片实际尺寸
    m_resizeCanvasSize = size;
    if (m_mode == ModeResize) {
        initResizeCanvas();
        viewport()->update();
    }
}

void ImageWorkspace::initResizeCanvas() {
    if (!m_pixmapItem || m_pixmapItem->pixmap().isNull()) return;
    
    // 确定画布大小：如果 m_resizeCanvasSize 为空或 (0,0)，使用图片实际尺寸
    QSizeF canvasSize;
    if (m_resizeCanvasSize.isEmpty() || (m_resizeCanvasSize.width() == 0 && m_resizeCanvasSize.height() == 0)) {
        canvasSize = m_pixmapItem->pixmap().size();
    } else {
        canvasSize = m_resizeCanvasSize;
    }
    
    // 设置固定画布大小（以 (0,0) 为原点）
    QRectF canvasRect(0, 0, canvasSize.width(), canvasSize.height());
    m_scene->setSceneRect(canvasRect);
    
    if (m_isFillMode) {
        // 填满模式：拉伸填充整个画布
        QSizeF imgSize = m_pixmapItem->pixmap().size();
        qreal sx = canvasRect.width() / imgSize.width();
        qreal sy = canvasRect.height() / imgSize.height();
        
        m_pixmapItem->setTransformOriginPoint(QPointF(0, 0));
        m_pixmapItem->setScale(1.0);
        m_pixmapItem->setTransform(QTransform::fromScale(sx, sy));
        m_pixmapItem->setPos(0, 0);
        
        m_scaleFactor = (sx + sy) / 2.0;
        emit scaleFactorChanged(m_scaleFactor);
    } else {
        // 正常模式：将图片居中并适配（保持比例）
        m_pixmapItem->setTransformOriginPoint(QPointF(0,0));
        m_pixmapItem->setTransform(QTransform()); // 清除非等比变换
        QSizeF imgSize = m_pixmapItem->pixmap().size();
        qreal sx = canvasRect.width()  / imgSize.width();
        qreal sy = canvasRect.height() / imgSize.height();
        qreal fitScale = qMin(sx, sy);
        if (fitScale <= 0) fitScale = 1.0;
        m_pixmapItem->setScale(fitScale);
        QSizeF scaled = imgSize * fitScale;
        QPointF offset((canvasRect.width()-scaled.width())/2.0,
                       (canvasRect.height()-scaled.height())/2.0);
        m_pixmapItem->setPos(offset);
        m_scaleFactor = fitScale;
        emit scaleFactorChanged(m_scaleFactor);
    }
    
    // 视图居中到画布中心
    centerOn(canvasRect.center());
}

void ImageWorkspace::clampImageInsideCanvas() {
    if (!m_pixmapItem || m_pixmapItem->pixmap().isNull()) return;
    if (m_mode != ModeResize) return; // 仅在 Resize 模式下约束
    
    QRectF canvas = m_scene->sceneRect();
    QRectF imgBounds = m_pixmapItem->mapToScene(m_pixmapItem->pixmap().rect()).boundingRect();
    QPointF currentPos = m_pixmapItem->pos();
    // 只有图片越界才回拉；允许图片比画布小并位于内部任意位置
    qreal dx = 0.0; qreal dy = 0.0;
    if (imgBounds.left() < canvas.left()) dx = canvas.left() - imgBounds.left();
    if (imgBounds.top() < canvas.top()) dy = canvas.top() - imgBounds.top();
    if (imgBounds.right() > canvas.right()) dx = canvas.right() - imgBounds.right();
    if (imgBounds.bottom() > canvas.bottom()) dy = canvas.bottom() - imgBounds.bottom();
    if (!qFuzzyIsNull(dx) || !qFuzzyIsNull(dy)) {
        m_pixmapItem->setPos(currentPos + QPointF(dx, dy));
    }
}

void ImageWorkspace::applyResizeZoom(qreal factor) {
    if (!m_pixmapItem || m_pixmapItem->pixmap().isNull()) return;
    qreal newScale = m_pixmapItem->scale() * factor;
    // 限制缩放范围（可调）
    if (newScale < 0.05) newScale = 0.05;
    if (newScale > 20.0) newScale = 20.0;
    m_pixmapItem->setScale(newScale);
    m_scaleFactor = newScale;
    emit scaleFactorChanged(m_scaleFactor);
    clampImageInsideCanvas();
    viewport()->update();
}

// ==================== 状态保存恢复辅助 ====================
void ImageWorkspace::saveImageItemState(ImageItemState &state) {
    if (!m_pixmapItem) return;
    state.pos = m_pixmapItem->pos();
    state.scale = m_pixmapItem->scale();
    state.transformOrigin = m_pixmapItem->transformOriginPoint();
    state.transform = m_pixmapItem->transform();
}

void ImageWorkspace::restoreImageItemState(const ImageItemState &state) {
    if (!m_pixmapItem) return;
    m_pixmapItem->setPos(state.pos);
    m_pixmapItem->setScale(state.scale);
    m_pixmapItem->setTransformOriginPoint(state.transformOrigin);
    m_pixmapItem->setTransform(state.transform);
    m_scaleFactor = state.scale;
    emit scaleFactorChanged(m_scaleFactor);
}

void ImageWorkspace::resetImageItemToOriginal() {
    if (!m_pixmapItem) return;
    // Crop/None 模式：图片在场景原点，无缩放，原点为左上角
    m_pixmapItem->setPos(0, 0);
    m_pixmapItem->setScale(1.0);
    m_pixmapItem->setTransformOriginPoint(QPointF(0, 0));
    m_pixmapItem->setTransform(QTransform()); // 清除所有变换（包括拉伸变换）
    m_scaleFactor = 1.0;
    emit scaleFactorChanged(m_scaleFactor);
}

// ==================== Resize 导出实现 ====================
QImage ImageWorkspace::getResizeResultImage() const {
    if (m_mode != ModeResize) return QImage();
    if (!m_pixmapItem || m_pixmapItem->pixmap().isNull()) return QImage();

    // 画布尺寸：sceneRect 即为期望导出尺寸
    QRectF canvasRect = m_scene->sceneRect();
    if (canvasRect.isEmpty()) return QImage();

    QSize outSize(qRound(canvasRect.width()), qRound(canvasRect.height()));
    if (outSize.isEmpty()) return QImage();

    QImage result(outSize, QImage::Format_ARGB32_Premultiplied);
    result.fill(m_resizeBackgroundColor); // 使用设置的背景色

    QPainter p(&result);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);

    // 获取图片的完整变换（包括 scale 和 transform）
    const QPixmap &px = m_pixmapItem->pixmap();
    QTransform itemTransform = m_pixmapItem->sceneTransform();
    
    // 绘制图片：使用完整的场景变换
    p.setTransform(itemTransform);
    p.drawPixmap(QPointF(0, 0), px);
    p.end();

    return result;
}

void ImageWorkspace::setResizeBackgroundColor(const QColor &color) {
    m_resizeBackgroundColor = color;
    if (m_mode == ModeResize) {
        viewport()->update();
    }
}

void ImageWorkspace::centerImageInCanvas() {
    if (m_mode != ModeResize) return;
    if (!m_pixmapItem || m_pixmapItem->pixmap().isNull()) return;
    
    QRectF canvas = m_scene->sceneRect();
    if (canvas.isEmpty()) return;
    
    qreal s = m_pixmapItem->scale();
    QSizeF scaledSize = m_pixmapItem->pixmap().size() * s;
    QPointF offset((canvas.width() - scaledSize.width()) / 2.0,
                   (canvas.height() - scaledSize.height()) / 2.0);
    m_pixmapItem->setPos(offset);
    clampImageInsideCanvas();
    viewport()->update();
}

void ImageWorkspace::toggleFillMode() {
    if (m_mode != ModeResize) return;
    if (!m_pixmapItem || m_pixmapItem->pixmap().isNull()) return;
    
    QRectF canvas = m_scene->sceneRect();
    if (canvas.isEmpty()) return;
    
    if (!m_isFillMode) {
        // 进入填满模式：保存当前状态，然后拉伸填充
        saveImageItemState(m_beforeFillState);
        
        QSizeF imgSize = m_pixmapItem->pixmap().size();
        qreal sx = canvas.width() / imgSize.width();
        qreal sy = canvas.height() / imgSize.height();
        
        m_pixmapItem->setScale(1.0);
        m_pixmapItem->setTransform(QTransform::fromScale(sx, sy));
        m_pixmapItem->setPos(0, 0);
        
        m_scaleFactor = (sx + sy) / 2.0;
        emit scaleFactorChanged(m_scaleFactor);
        
        m_isFillMode = true;
    } else {
        // 退出填满模式：恢复之前的状态
        restoreImageItemState(m_beforeFillState);
        m_isFillMode = false;
    }
    
    viewport()->update();
}