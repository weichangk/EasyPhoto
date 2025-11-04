#pragma once
#include "globalview.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QImage>
#include <QPixmap>

class ImageWorkspace : public QGraphicsView {
    Q_OBJECT

public:
    explicit ImageWorkspace(QWidget *parent = nullptr);
    void loadImage(const QString &filePath); // 加载图片
    void setFitView();                       // 适应窗口
    void resetView();                        // 还原原始大小
    void zoomIn();                           // 放大
    void zoomOut();                          // 缩小
    // 以百分比设置缩放（相对于原始 1:1 大小）。
    // percent = 100 表示 100%（原始大小），200 表示放大 2 倍。
    // 传入 <= 0 的值将被忽略。
    void zoomToPercent(double percent);

    // 工作模式：普通 / 裁剪 / Resize(固定画布大小，图片可在其中移动缩放)
    enum WorkspaceMode { ModeNone=0, ModeCrop, ModeResize };
    void setWorkspaceMode(WorkspaceMode mode);
    WorkspaceMode workspaceMode() const { return m_mode; }

    // Resize 画布设置（例如 1280x720 用于 YouTube 缩略图）
    // 注意：传入 QSize(0,0) 或不设置时，画布将使用图片实际尺寸
    void setResizeCanvasSize(const QSize &size); // 设置目标画布大小（进入或已在 ModeResize 都可调用）
    QSize resizeCanvasSize() const { return m_resizeCanvasSize; }
    
    // Resize 模式背景色设置（默认透明 Qt::transparent）
    void setResizeBackgroundColor(const QColor &color);
    QColor resizeBackgroundColor() const { return m_resizeBackgroundColor; }
    
    // Resize 模式图片快速调整
    void centerImageInCanvas();  // 将图片居中到画布
    void toggleFillMode();       // 切换填满模式（拉伸填充）
    bool isFillMode() const { return m_isFillMode; }

    // 裁剪比例模式
    enum CropAspectRatioMode {
        CropAspectFree = 0,      // 自由（不限制比例）
        CropAspectOriginal,      // 原始（图片原始比例）
        CropAspectSquare,        // 正方形 1:1
        CropAspect16_9,          // 16:9
        CropAspect9_16,          // 9:16
        CropAspect4_5,           // 4:5
        CropAspect5_4,           // 5:4
        CropAspect3_4,           // 3:4
        CropAspect4_3,           // 4:3
        CropAspect2_3,           // 2:3
        CropAspect3_2,           // 3:2
        CropAspect5_7,           // 5:7
        CropAspect7_5,           // 7:5
        CropAspect1_2,           // 1:2
        CropAspect2_1            // 2:1
    };
    void setCropAspectRatioMode(CropAspectRatioMode mode);
    CropAspectRatioMode cropAspectRatioMode() const { return m_cropAspectMode; }

    QRectF getCropRect() const;              // 获取裁剪区域(场景坐标)
    QRect getCropRectInImage() const;        // 获取裁剪区域(图片坐标)
    void clearCropRect();                    // 清除裁剪选区
    QPixmap getCroppedImage() const;         // 获取裁剪后的图片
    void resetCropRect();                    // 重置裁剪区域为当前可见图片区域
    // Resize 模式导出：返回当前画布合成后的图像（透明背景）
    QImage getResizeResultImage() const;     // 仅在 ModeResize 下有效，其它模式返回空 QImage
    
    double getScaleFactor() const { return m_scaleFactor; } // 获取当前缩放比例

signals:
    void cropRectChanged(const QRectF &rect); // 裁剪区域改变信号
    void scaleFactorChanged(double scale);    // 缩放比例改变信号
    void modeChanged(WorkspaceMode mode);      // 模式切换信号
    void imageSizeChanged(const QSize &size);  // 图片实际大小改变信号

protected:
    void wheelEvent(QWheelEvent *event) override;        // 处理滚轮事件
    void mousePressEvent(QMouseEvent *event) override;   // 处理鼠标按下
    void mouseMoveEvent(QMouseEvent *event) override;    // 处理鼠标移动
    void mouseReleaseEvent(QMouseEvent *event) override; // 处理鼠标释放
    void paintEvent(QPaintEvent *event) override;        // 绘制缩放比例标签
    void resizeEvent(QResizeEvent *event) override;      // 处理窗口尺寸改变

private:
    QGraphicsScene *m_scene;
    QGraphicsPixmapItem *m_pixmapItem;
    double m_scaleFactor;  // 缩放比例
    bool m_isPanning;      // 是否正在拖动
    QPoint m_lastMousePos; // 上一次鼠标位置
    
    // 模式相关
    WorkspaceMode m_mode;           // 当前模式
    CropAspectRatioMode m_cropAspectMode; // 裁剪比例模式

    // Resize 模式相关
    QSize m_resizeCanvasSize;      // 画布逻辑尺寸（场景大小）
    QColor m_resizeBackgroundColor = Qt::transparent; // Resize 导出背景色
    bool m_isFillMode = false;     // 是否开启填满模式（拉伸填充画布）
    bool m_isImageDragging = false; // 是否在 Resize 模式下拖动图片
    QPoint m_imageDragStartPos;     // 拖动开始时鼠标（视口坐标）
    QPointF m_imageItemStartPos;    // 拖动开始时图片项的 pos
    
    // 模式状态保存（用于模式切换时恢复）
    struct ImageItemState {
        QPointF pos;
        qreal scale;
        QPointF transformOrigin;
        QTransform transform;  // 保存完整变换（支持非等比缩放）
    };
    ImageItemState m_cropModeState;   // Crop/None 模式图片状态
    ImageItemState m_resizeModeState; // Resize 模式图片状态
    ImageItemState m_beforeFillState; // 填满前的状态（用于恢复）

    // 裁剪系统：视口坐标中的裁剪矩形与交互
    enum OverlayHandle { HandleNone=0, HandleTopLeft, HandleTopRight, HandleBottomLeft, HandleBottomRight,
                         HandleTop, HandleBottom, HandleLeft, HandleRight, HandleCenter };
    QRect m_cropOverlay;            // 视口坐标中的裁剪矩形（视觉固定）
    QRectF m_savedCropOverlayScene; // 保存的选框场景坐标（用于模式切换恢复）
    OverlayHandle m_overlayHandle;  // 当前拖拽句柄
    bool m_draggingOverlay;         // 是否正在拖拽
    QPoint m_dragStartPos;          // 拖拽开始时视口坐标
    QRect m_dragStartOverlay;       // 拖拽开始时矩形
    int m_handleVisualSize = 10;    // 控制点显示大小（像素）

    // 辅助：将视口裁剪矩形转换/约束到图片范围
    QRectF overlayViewportRectToScene(const QRect &vpRect) const; // 视口->场景
    QRect overlaySceneRectToViewport(const QRectF &sceneRect) const; // 场景->视口
    void initOverlayFromVisibleImage();      // 初始化覆盖矩形
    void clampOverlayToImage(QRect &overlay, bool preserveSize = false); // 约束覆盖矩形不超出图片
    qreal getMinScaleForCropOverlay() const;  // 获取覆盖选区所需的最小缩放
    OverlayHandle hitTestOverlayHandle(const QPoint &vpPos) const; // 命中测试
    void updateCursorForHandle(OverlayHandle h);
    void paintOverlay(QPainter &painter);    // 绘制覆盖
    
    // 裁剪比例辅助函数
    qreal getAspectRatio() const;            // 获取当前比例模式的宽高比
    QRect constrainToAspectRatio(const QRect &rect, OverlayHandle handle) const; // 按比例约束矩形
    
    void updateScaleFactor();       // 更新并发射缩放比例信号

    // Resize 模式辅助
    void initResizeCanvas();        // 初始化/重设场景大小与图片初始位置
    void clampImageInsideCanvas();  // 保证图片在当前画布范围内（不允许移出）
    void applyResizeZoom(qreal factor); // 在 Resize 模式下缩放图片并保持约束
    
    // 状态保存恢复
    void saveImageItemState(ImageItemState &state);
    void restoreImageItemState(const ImageItemState &state);
    void resetImageItemToOriginal(); // 重置图片项到原始状态（Crop/None 模式用）
};