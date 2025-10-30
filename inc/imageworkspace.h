#pragma once
#include "globalview.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QImage>
#include <QPixmap>

// 前向声明
class ImageWorkspace;

// 裁剪遮罩项：只负责绘制半透明遮罩（图片区域外的部分）
class CropMaskItem : public QGraphicsItem {
public:
    explicit CropMaskItem(QGraphicsItem *parent = nullptr);
    void setImageBounds(const QRectF &bounds);   // 设置图片边界 (场景坐标)
    void setCropRect(const QRectF &cropRect);    // 设置当前裁剪区域 (场景坐标)

protected:
    QRectF boundingRect() const override;        // 遮罩的包围矩形（图片区域大小）
    QPainterPath shape() const override;         // 返回空路径，不拦截鼠标事件
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QRectF m_imageBounds;  // 图片边界
    QRectF m_cropRect;     // 当前裁剪区域
};

// 裁剪选区矩形项（只负责选区框及控制点，不再绘制遮罩）
class CropRectItem : public QGraphicsRectItem {
public:
    explicit CropRectItem(ImageWorkspace *viewer, QGraphicsItem *parent = nullptr);
    void updateHandles();
    void setImageBounds(const QRectF &bounds); // 设置图片边界
    
protected:
    QPainterPath shape() const override; // 定义可交互区域(只包含控制点和中心锚点)
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    
private:
    enum HandlePosition {
        None = 0,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
        Top,
        Bottom,
        Left,
        Right,
        Center
    };
    
    HandlePosition getHandleAt(const QPointF &pos);
    QRectF getHandleRect(HandlePosition pos) const;
    QRectF constrainRectToBounds(const QRectF &sceneRect) const; // 限制矩形在边界内（调整大小用）
    QRectF constrainMoveInBounds(const QRectF &sceneRect) const;  // 限制移动在边界内（保持大小）
    
    HandlePosition m_currentHandle;
    QPointF m_dragStartPos;      // 场景坐标
    QRectF m_dragStartRect;      // 场景坐标的矩形
    bool m_hasMoved;             // 标记是否发生了移动
    const qreal m_handleSize = 8.0;
    const qreal m_anchorRadius = 12.0; // 中心锚点半径
    QRectF m_imageBounds;        // 图片边界（场景坐标）
    ImageWorkspace *m_viewer;       // 所属的 ImageWorkspace，用于通知选区变化
};

class ImageWorkspace : public QGraphicsView {
    Q_OBJECT

public:
    explicit ImageWorkspace(QWidget *parent = nullptr);
    void loadImage(const QString &filePath); // 加载图片
    void setFitView();                       // 适应窗口
    void resetView();                        // 还原原始大小
    void zoomIn();                           // 放大
    void zoomOut();                          // 缩小

    // 裁剪功能
    void enableCropMode(bool enable);        // 启用/禁用裁剪模式
    bool isCropMode() const;                 // 是否处于裁剪模式
    QRectF getCropRect() const;              // 获取裁剪区域(场景坐标)
    QRect getCropRectInImage() const;        // 获取裁剪区域(图片坐标)
    void clearCropRect();                    // 清除裁剪选区
    QPixmap getCroppedImage() const;         // 获取裁剪后的图片
    void resetCropRect();                    // 重置裁剪区域到图片大小

    // 选区几何变化时调用（供 CropRectItem 在拖动/缩放时使用）
    void cropRectItemGeometryChanged();
    friend class CropRectItem;
    inline void notifyCropRectChangedFromItem() { cropRectItemGeometryChanged(); }
    
    double getScaleFactor() const { return m_scaleFactor; } // 获取当前缩放比例

signals:
    void cropRectChanged(const QRectF &rect); // 裁剪区域改变信号
    void scaleFactorChanged(double scale);    // 缩放比例改变信号

protected:
    void wheelEvent(QWheelEvent *event) override;        // 处理滚轮事件
    void mousePressEvent(QMouseEvent *event) override;   // 处理鼠标按下
    void mouseMoveEvent(QMouseEvent *event) override;    // 处理鼠标移动
    void mouseReleaseEvent(QMouseEvent *event) override; // 处理鼠标释放
    void paintEvent(QPaintEvent *event) override;        // 绘制缩放比例标签

private:
    QGraphicsScene *m_scene;
    QGraphicsPixmapItem *m_pixmapItem;
    double m_scaleFactor;  // 缩放比例
    bool m_isPanning;      // 是否正在拖动
    QPoint m_lastMousePos; // 上一次鼠标位置
    
    // 裁剪相关
    bool m_cropMode;                // 是否处于裁剪模式
    CropRectItem *m_cropRect;       // 裁剪选区矩形
    CropMaskItem *m_cropMask;       // 裁剪遮罩
    
    void updateScaleFactor();       // 更新并发射缩放比例信号

// （保持上方 public 方法定义）
};
