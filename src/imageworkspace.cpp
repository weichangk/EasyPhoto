#include "imageworkspace.h"
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QPaintEvent>
#include <QFontMetrics>
#include <QtMath>

// ==================== CropMaskItem 实现 ====================
CropMaskItem::CropMaskItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , m_imageBounds()
    , m_cropRect()
{
    setZValue(90); // 在图片之上、裁剪框之下
    setAcceptedMouseButtons(Qt::NoButton); // 不处理事件
    setFlag(QGraphicsItem::ItemHasNoContents, false); // 确保会绘制
}

void CropMaskItem::setImageBounds(const QRectF &bounds) {
    if (m_imageBounds == bounds) return;
    prepareGeometryChange();
    m_imageBounds = bounds;
    update();
}

void CropMaskItem::setCropRect(const QRectF &cropRect) {
    if (m_cropRect == cropRect) return;
    m_cropRect = cropRect;
    update();
}

QRectF CropMaskItem::boundingRect() const {
    return m_imageBounds; // 遮罩绘制区域限定为图片范围
}

QPainterPath CropMaskItem::shape() const {
    // 返回空路径，确保不拦截任何鼠标事件
    return QPainterPath();
}

void CropMaskItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (m_imageBounds.isNull()) return;

    // 计算本地裁剪区域（CropRect 是场景坐标，这里 item 没有位移，直接映射）
    QRectF cropLocal = m_cropRect;
    // 遮罩: 图片范围减去裁剪区域
    QPainterPath path;
    path.addRect(m_imageBounds);
    path.addRect(cropLocal);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->fillPath(path, QColor(0, 0, 0, 100));
}

// ==================== CropRectItem 实现 ====================
CropRectItem::CropRectItem(ImageWorkspace *viewer, QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
    , m_currentHandle(None)
    , m_hasMoved(false)
    , m_imageBounds(QRectF())
    , m_viewer(viewer)
{
    setFlags(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    setZValue(100);
    QPen pen(QColor(255, 255, 255), 2, Qt::SolidLine);
    setPen(pen);
    setBrush(Qt::NoBrush);

    // 设置为透明,只在 shape() 中定义可交互区域
    setAcceptedMouseButtons(Qt::LeftButton);
}

void CropRectItem::setImageBounds(const QRectF &bounds) {
    m_imageBounds = bounds;
}

QPainterPath CropRectItem::shape() const {
    // 定义可交互区域:只包含8个控制点和中心锚点,其他区域透明穿透
    QPainterPath path;
    
    // 添加8个角/边控制点
    QList<HandlePosition> handles = {TopLeft, TopRight, BottomLeft, BottomRight,
                                     Top, Bottom, Left, Right};
    for (auto pos : handles) {
        path.addRect(getHandleRect(pos));
    }
    
    // 添加中心锚点(圆形)
    QRectF r = rect();
    path.addEllipse(r.center(), m_anchorRadius, m_anchorRadius);
    
    return path;
}

void CropRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF r = rect();

    // 绘制选区边框
    painter->setPen(QPen(QColor(255, 255, 255), 2, Qt::SolidLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(r);

    // 绘制三等分线(九宫格)
    painter->setPen(QPen(QColor(255, 255, 255), 1, Qt::DashLine));
    qreal w = r.width() / 3.0;
    qreal h = r.height() / 3.0;
    painter->drawLine(QPointF(r.left() + w, r.top()), QPointF(r.left() + w, r.bottom()));
    painter->drawLine(QPointF(r.left() + 2*w, r.top()), QPointF(r.left() + 2*w, r.bottom()));
    painter->drawLine(QPointF(r.left(), r.top() + h), QPointF(r.right(), r.top() + h));
    painter->drawLine(QPointF(r.left(), r.top() + 2*h), QPointF(r.right(), r.top() + 2*h));

    // 绘制8个角/边控制点
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(255, 255, 255));
    QList<HandlePosition> handles = {TopLeft, TopRight, BottomLeft, BottomRight,
                                     Top, Bottom, Left, Right};
    for (auto pos : handles) {
        painter->drawRect(getHandleRect(pos));
    }
    
    // 绘制中心锚点(圆形,用于移动整个选区)
    QPointF center = r.center();
    qreal anchorRadius = m_anchorRadius;
    
    // 外圈(白色描边)
    painter->setPen(QPen(QColor(255, 255, 255), 2));
    painter->setBrush(QColor(100, 100, 100, 180));
    painter->drawEllipse(center, anchorRadius, anchorRadius);
    
    // 内圈(更小的白色实心圆)
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(255, 255, 255));
    painter->drawEllipse(center, anchorRadius * 0.4, anchorRadius * 0.4);

    // 绘制尺寸标签(选区内底部中央)
    QString sizeText = QString("%1 × %2").arg((int)r.width()).arg((int)r.height());
    QFont font;
    font.setPixelSize(14);
    font.setBold(false);
    painter->setFont(font);
    
    QFontMetrics fm(font);
    QRect textRect = fm.boundingRect(sizeText);
    int padding = 6;
    int labelWidth = textRect.width() + padding * 2;
    int labelHeight = textRect.height() + padding;
    
    // 标签位置:选区内底部中央,距离底边 10 像素
    QPointF labelPos(r.center().x() - labelWidth / 2.0, r.bottom() - labelHeight - 10);
    QRectF labelBgRect(labelPos, QSizeF(labelWidth, labelHeight));
    
    // 绘制标签背景(深色半透明)
    painter->setBrush(QColor(0, 0, 0, 160));
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(labelBgRect, 3, 3);
    
    // 绘制文字
    painter->setPen(QColor(255, 255, 255));
    painter->drawText(labelBgRect, Qt::AlignCenter, sizeText);
}

QRectF CropRectItem::getHandleRect(HandlePosition pos) const {
    QRectF r = rect();
    qreal half = m_handleSize / 2.0;
    
    switch (pos) {
        case TopLeft:     return QRectF(r.topLeft() - QPointF(half, half), QSizeF(m_handleSize, m_handleSize));
        case TopRight:    return QRectF(r.topRight() - QPointF(half, half), QSizeF(m_handleSize, m_handleSize));
        case BottomLeft:  return QRectF(r.bottomLeft() - QPointF(half, half), QSizeF(m_handleSize, m_handleSize));
        case BottomRight: return QRectF(r.bottomRight() - QPointF(half, half), QSizeF(m_handleSize, m_handleSize));
        case Top:         return QRectF(QPointF(r.center().x() - half, r.top() - half), QSizeF(m_handleSize, m_handleSize));
        case Bottom:      return QRectF(QPointF(r.center().x() - half, r.bottom() - half), QSizeF(m_handleSize, m_handleSize));
        case Left:        return QRectF(QPointF(r.left() - half, r.center().y() - half), QSizeF(m_handleSize, m_handleSize));
        case Right:       return QRectF(QPointF(r.right() - half, r.center().y() - half), QSizeF(m_handleSize, m_handleSize));
        default:          return QRectF();
    }
}

CropRectItem::HandlePosition CropRectItem::getHandleAt(const QPointF &pos) {
    QRectF r = rect();
    
    // 优先检查中心锚点(圆形区域)
    QPointF center = r.center();
    qreal distToCenter = QLineF(center, pos).length();
    if (distToCenter <= m_anchorRadius) {
        return Center;
    }
    
    // 检查8个角/边控制点
    QList<HandlePosition> handles = {TopLeft, TopRight, BottomLeft, BottomRight, 
                                      Top, Bottom, Left, Right};
    for (auto h : handles) {
        if (getHandleRect(h).contains(pos)) {
            return h;
        }
    }
    
    // 其他区域不响应(实现鼠标穿透效果)
    return None;
}

void CropRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_currentHandle = getHandleAt(event->pos());
        
        // 如果点击的不是控制点或中心锚点，忽略事件让其穿透
        if (m_currentHandle == None) {
            event->ignore();
            return;
        }
        
        m_dragStartPos = event->scenePos();  // 使用场景坐标
        // 使用逻辑矩形（场景坐标）：当前 item 的左上角 + 当前 rect 尺寸，避免 sceneBoundingRect 因边界约束造成尺寸跳变
        m_dragStartRect = QRectF(scenePos(), rect().size());
        m_hasMoved = false;  // 重置移动标志
        event->accept();
    } else {
        event->ignore();
    }
}

QRectF CropRectItem::constrainRectToBounds(const QRectF &sceneRect) const {
    if (m_imageBounds.isEmpty()) {
        return sceneRect;
    }
    
    QRectF constrained = sceneRect.normalized();
    
    // 直接在场景坐标系中限制
    if (constrained.left() < m_imageBounds.left()) {
        constrained.setLeft(m_imageBounds.left());
    }
    
    if (constrained.top() < m_imageBounds.top()) {
        constrained.setTop(m_imageBounds.top());
    }
    
    if (constrained.right() > m_imageBounds.right()) {
        constrained.setRight(m_imageBounds.right());
    }
    
    if (constrained.bottom() > m_imageBounds.bottom()) {
        constrained.setBottom(m_imageBounds.bottom());
    }
    
    return constrained;
}

QRectF CropRectItem::constrainMoveInBounds(const QRectF &sceneRect) const {
    if (m_imageBounds.isEmpty()) {
        return sceneRect;
    }
    
    // 保存原始大小，确保移动时大小绝对不变
    const qreal width = sceneRect.width();
    const qreal height = sceneRect.height();
    
    // 计算新的左上角位置
    qreal newX = sceneRect.x();
    qreal newY = sceneRect.y();
    
    // 限制 X 坐标
    if (newX < m_imageBounds.left()) {
        newX = m_imageBounds.left();
    } else if (newX + width > m_imageBounds.right()) {
        newX = m_imageBounds.right() - width;
    }
    
    // 限制 Y 坐标
    if (newY < m_imageBounds.top()) {
        newY = m_imageBounds.top();
    } else if (newY + height > m_imageBounds.bottom()) {
        newY = m_imageBounds.bottom() - height;
    }
    
    // 创建新矩形，严格使用原始大小
    return QRectF(newX, newY, width, height);
}

void CropRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_currentHandle == None) {
        event->ignore();
        return;
    }
    
    m_hasMoved = true;  // 标记已发生移动
    
    QPointF sceneDelta = event->scenePos() - m_dragStartPos;
    QRectF newSceneRect = m_dragStartRect;
    
    if (m_currentHandle == Center) {
        // 移动整个选区 - 使用原始大小创建新矩形
        qreal newX = m_dragStartRect.x() + sceneDelta.x();
        qreal newY = m_dragStartRect.y() + sceneDelta.y();
        newSceneRect = QRectF(newX, newY, m_dragStartRect.width(), m_dragStartRect.height());
        
        // 限制在图片边界内（保持大小不变）
        newSceneRect = constrainMoveInBounds(newSceneRect);
        
        // 转换为本地坐标系统
        setRect(0, 0, newSceneRect.width(), newSceneRect.height());
        setPos(newSceneRect.topLeft());
        
        // 通知更新遮罩
    if (m_viewer) m_viewer->notifyCropRectChangedFromItem();
        update();
        event->accept();
        return;
    }
    
    // 调整选区大小（在场景坐标系中）
    switch (m_currentHandle) {
        case TopLeft:
            newSceneRect.setTopLeft(m_dragStartRect.topLeft() + sceneDelta);
            break;
        case TopRight:
            newSceneRect.setTopRight(m_dragStartRect.topRight() + sceneDelta);
            break;
        case BottomLeft:
            newSceneRect.setBottomLeft(m_dragStartRect.bottomLeft() + sceneDelta);
            break;
        case BottomRight:
            newSceneRect.setBottomRight(m_dragStartRect.bottomRight() + sceneDelta);
            break;
        case Top:
            newSceneRect.setTop(m_dragStartRect.top() + sceneDelta.y());
            break;
        case Bottom:
            newSceneRect.setBottom(m_dragStartRect.bottom() + sceneDelta.y());
            break;
        case Left:
            newSceneRect.setLeft(m_dragStartRect.left() + sceneDelta.x());
            break;
        case Right:
            newSceneRect.setRight(m_dragStartRect.right() + sceneDelta.x());
            break;
        default:
            break;
    }
    
    newSceneRect = newSceneRect.normalized();
    
    // 限制在图片边界内
    newSceneRect = constrainRectToBounds(newSceneRect);
    
    // 确保矩形有效（宽高至少为20像素）
    if (newSceneRect.width() >= 20 && newSceneRect.height() >= 20) {
        // 转换为本地坐标系统
        setRect(0, 0, newSceneRect.width(), newSceneRect.height());
        setPos(newSceneRect.topLeft());
    }
    
    if (m_viewer) m_viewer->notifyCropRectChangedFromItem();
    update();
    event->accept();
}

void CropRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton && m_currentHandle != None) {
        // 使用当前逻辑矩形（避免 sceneBoundingRect 可能的放大）
        QRectF currentSceneRect(scenePos(), rect().size());

        if (m_hasMoved) {
            if (m_currentHandle == Center) {
                // 已移动：保持大小不变，仅位置对齐到边界
                QRectF finalRect = constrainMoveInBounds(currentSceneRect);
                setRect(0, 0, finalRect.width(), finalRect.height());
                setPos(finalRect.topLeft());
            } else {
                // 已调整大小：限制在边界内
                QRectF bounded = constrainRectToBounds(currentSceneRect);
                setRect(0, 0, bounded.width(), bounded.height());
                setPos(bounded.topLeft());
            }
            if (m_viewer) m_viewer->notifyCropRectChangedFromItem();
            update();
        } // 未移动则不做任何尺寸/位置修改，避免尺寸跳变
        
        m_currentHandle = None;
        m_hasMoved = false;
        
        // 释放后，根据当前鼠标位置重新设置光标
        HandlePosition handle = getHandleAt(event->pos());
        if (handle == None) {
            // 如果在非交互区域，取消光标让 View 的光标生效
            m_viewer->unsetCursor();
        } else {
            // 如果在控制点或锚点上，设置对应的光标
            switch (handle) {
                case TopLeft:
                case BottomRight:
                    m_viewer->setCursor(Qt::SizeFDiagCursor);
                    break;
                case TopRight:
                case BottomLeft:
                    m_viewer->setCursor(Qt::SizeBDiagCursor);
                    break;
                case Top:
                case Bottom:
                    m_viewer->setCursor(Qt::SizeVerCursor);
                    break;
                case Left:
                case Right:
                    m_viewer->setCursor(Qt::SizeHorCursor);
                    break;
                case Center:
                    m_viewer->setCursor(Qt::SizeAllCursor);
                    break;
                default:
                    m_viewer->unsetCursor();
                    break;
            }
        }
    }
    event->accept();
}

void CropRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    HandlePosition handle = getHandleAt(event->pos());
    
    switch (handle) {
        case TopLeft:
        case BottomRight:
            m_viewer->setCursor(Qt::SizeFDiagCursor);
            break;
        case TopRight:
        case BottomLeft:
            m_viewer->setCursor(Qt::SizeBDiagCursor);
            break;
        case Top:
        case Bottom:
            m_viewer->setCursor(Qt::SizeVerCursor);
            break;
        case Left:
        case Right:
            m_viewer->setCursor(Qt::SizeHorCursor);
            break;
        case Center:
            m_viewer->setCursor(Qt::SizeAllCursor); // 中心锚点显示移动光标
            break;
        default:
            m_viewer->unsetCursor(); // 取消光标设置，让 View 的光标生效（穿透效果）
            break;
    }
}

void CropRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
    m_viewer->unsetCursor(); // 离开时取消光标，恢复 View 的光标
}

// ==================== ImageWorkspace 实现 ====================
ImageWorkspace::ImageWorkspace(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_pixmapItem(new QGraphicsPixmapItem()),
    m_scaleFactor(1.0),
    m_isPanning(false),
    m_cropMode(false),
    m_cropRect(nullptr),
    m_cropMask(nullptr) {
    setObjectName("ImageWorkspace");
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(m_scene);
    m_scene->addItem(m_pixmapItem);

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
    m_scene->setSceneRect(pixmap.rect());
    setFitView();
    // 如果已有裁剪遮罩与裁剪框，更新其边界
    if (m_cropMask) m_cropMask->setImageBounds(m_pixmapItem->sceneBoundingRect());
    if (m_cropRect) m_cropRect->setImageBounds(m_pixmapItem->sceneBoundingRect());
    cropRectItemGeometryChanged();
}

void ImageWorkspace::setFitView() {
    fitInView(m_pixmapItem, Qt::KeepAspectRatio);
    updateScaleFactor(); // 计算fitInView后的实际缩放比例
}

void ImageWorkspace::resetView() {
    resetTransform();
    m_scaleFactor = 1.0;
    emit scaleFactorChanged(m_scaleFactor);
    viewport()->update();
}

void ImageWorkspace::zoomIn() {
    scale(1.01, 1.01);  // 每次放大1%
    m_scaleFactor *= 1.01;
    emit scaleFactorChanged(m_scaleFactor);
    viewport()->update();
}

void ImageWorkspace::zoomOut() {
    scale(1 / 1.01, 1 / 1.01);  // 每次缩小1%
    m_scaleFactor /= 1.01;
    emit scaleFactorChanged(m_scaleFactor);
    viewport()->update();
}

void ImageWorkspace::updateScaleFactor() {
    // 计算当前变换矩阵的实际缩放比例
    QTransform t = transform();
    m_scaleFactor = qSqrt(t.m11() * t.m11() + t.m12() * t.m12());
    emit scaleFactorChanged(m_scaleFactor);
    viewport()->update(); // 触发重绘以更新缩放显示
}

void ImageWorkspace::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        zoomIn();
    } else {
        zoomOut();
    }
}

void ImageWorkspace::enableCropMode(bool enable) {
    m_cropMode = enable;
    
    if (enable) {
        // 进入裁剪模式
        setCursor(Qt::ArrowCursor);
        
        // 创建裁剪框和遮罩，默认覆盖整个图片
        if (!m_pixmapItem->pixmap().isNull()) {
            QRectF imageRect = m_pixmapItem->sceneBoundingRect();
            if (!m_cropMask) {
                m_cropMask = new CropMaskItem();
                m_scene->addItem(m_cropMask);
                m_cropMask->setImageBounds(imageRect);
            }
            if (!m_cropRect) {
                m_cropRect = new CropRectItem(this);
                m_scene->addItem(m_cropRect);
                m_cropRect->setImageBounds(imageRect);
                m_cropRect->setRect(QRectF(0, 0, imageRect.width(), imageRect.height()));
                m_cropRect->setPos(imageRect.topLeft());
            }
            cropRectItemGeometryChanged();
        }
    } else {
        // 退出裁剪模式
        setCursor(Qt::ArrowCursor);
        clearCropRect();
    }
}

bool ImageWorkspace::isCropMode() const {
    return m_cropMode;
}

void ImageWorkspace::resetCropRect() {
    if (m_cropRect && !m_pixmapItem->pixmap().isNull()) {
        QRectF imageRect = m_pixmapItem->sceneBoundingRect();
        m_cropRect->setImageBounds(imageRect);
        m_cropRect->setRect(QRectF(0, 0, imageRect.width(), imageRect.height()));
        m_cropRect->setPos(imageRect.topLeft());
        if (m_cropMask) m_cropMask->setImageBounds(imageRect);
        cropRectItemGeometryChanged();
    }
}

QRectF ImageWorkspace::getCropRect() const {
    if (m_cropRect) {
        QRectF rect = m_cropRect->rect();
        rect.translate(m_cropRect->pos());
        return rect;
    }
    return QRectF();
}

QRect ImageWorkspace::getCropRectInImage() const {
    if (!m_cropRect || m_pixmapItem->pixmap().isNull()) {
        return QRect();
    }
    
    QRectF sceneRect = getCropRect();
    QRectF itemRect = m_pixmapItem->mapRectFromScene(sceneRect);
    
    return itemRect.toRect();
}

void ImageWorkspace::clearCropRect() {
    if (m_cropRect) {
        m_scene->removeItem(m_cropRect);
        delete m_cropRect;
        m_cropRect = nullptr;
    }
    if (m_cropMask) {
        m_scene->removeItem(m_cropMask);
        delete m_cropMask;
        m_cropMask = nullptr;
    }
}

QPixmap ImageWorkspace::getCroppedImage() const {
    if (!m_cropRect || m_pixmapItem->pixmap().isNull()) {
        return QPixmap();
    }
    
    QRect cropRect = getCropRectInImage();
    return m_pixmapItem->pixmap().copy(cropRect);
}

void ImageWorkspace::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // 先传递给 scene，让 CropRectItem 有机会处理
        QGraphicsView::mousePressEvent(event);
        
        // 如果事件没有被接受（穿透了），则启动平移
        if (!event->isAccepted()) {
            m_isPanning = true;
            m_lastMousePos = event->pos();
            setCursor(Qt::ClosedHandCursor);
            event->accept();
        }
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void ImageWorkspace::mouseMoveEvent(QMouseEvent *event) {
    if (m_isPanning) {
        QPointF delta = mapToScene(event->pos()) - mapToScene(m_lastMousePos);
        translate(delta.x(), delta.y());
        m_lastMousePos = event->pos();
    }
    QGraphicsView::mouseMoveEvent(event);
}

// 内部辅助：裁剪框几何变化
void ImageWorkspace::cropRectItemGeometryChanged() {
    if (!m_cropRect) return;
    QRectF sceneRect = getCropRect();
    if (m_cropMask) m_cropMask->setCropRect(sceneRect);
    emit cropRectChanged(sceneRect);
}

void ImageWorkspace::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (m_isPanning) {
            m_isPanning = false;
            // 裁剪模式下恢复箭头光标，非裁剪模式也恢复箭头光标
            setCursor(Qt::ArrowCursor);
        }
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void ImageWorkspace::paintEvent(QPaintEvent *event) {
    // 先绘制基类内容（图片和场景）
    QGraphicsView::paintEvent(event);
    
    // 在视图左下角绘制缩放比例
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 准备文字
    QString scaleText = QString("%1%").arg(qRound(m_scaleFactor * 100));
    QFont font;
    font.setPixelSize(14);
    font.setBold(true);
    painter.setFont(font);
    
    // 计算文字大小
    QFontMetrics fm(font);
    QRect textRect = fm.boundingRect(scaleText);
    int padding = 8;
    int labelWidth = textRect.width() + padding * 2;
    int labelHeight = textRect.height() + padding;
    
    // 位置：左下角，距离边缘 10 像素
    int margin = 10;
    QRect labelBgRect(margin, viewport()->height() - labelHeight - margin, 
                     labelWidth, labelHeight);
    
    // 绘制半透明背景
    painter.setBrush(QColor(0, 0, 0, 160));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(labelBgRect, 4, 4);
    
    // 绘制文字
    painter.setPen(QColor(255, 255, 255));
    painter.drawText(labelBgRect, Qt::AlignCenter, scaleText);
}
