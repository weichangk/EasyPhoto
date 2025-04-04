#pragma once
#include "globalview.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QImage>
#include <QPixmap>

class ImageViewer : public QGraphicsView {
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = nullptr);
    void loadImage(const QString &filePath); // 加载图片
    void setFitView();                       // 适应窗口
    void resetView();                        // 还原原始大小
    void zoomIn();                           // 放大
    void zoomOut();                          // 缩小

protected:
    void wheelEvent(QWheelEvent *event) override;        // 处理滚轮事件
    void mousePressEvent(QMouseEvent *event) override;   // 处理鼠标按下
    void mouseMoveEvent(QMouseEvent *event) override;    // 处理鼠标移动
    void mouseReleaseEvent(QMouseEvent *event) override; // 处理鼠标释放

private:
    QGraphicsScene *m_scene;
    QGraphicsPixmapItem *m_pixmapItem;
    double m_scaleFactor;  // 缩放比例
    bool m_isPanning;      // 是否正在拖动
    QPoint m_lastMousePos; // 上一次鼠标位置
};
