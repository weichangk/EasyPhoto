/*
 * @Author: weick
 * @Date: 2024-01-08 23:09:37
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-09 00:13:53
 */

#include "inc/arotatingpixmapwidget.h"

ARotatingPixmapItem::ARotatingPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent) {
    setTransformOriginPoint(pixmap.width() / 2.0, pixmap.height() / 2.0);

    // 创建旋转动画
    m_RotationAnimation = new QPropertyAnimation(this, "rotation");
    m_RotationAnimation->setDuration(2000); // 旋转动画时长，单位为毫秒
    m_RotationAnimation->setStartValue(0);  // 起始角度
    m_RotationAnimation->setEndValue(360);  // 结束角度
    m_RotationAnimation->setLoopCount(-1);  // 无限循环
}

void ARotatingPixmapItem::start() {
    // 启动动画
    m_RotationAnimation->start();
}

void ARotatingPixmapItem::stop() {
    // 停止动画
    m_RotationAnimation->stop();
}

AWidgetWithRotatingItem::AWidgetWithRotatingItem(QPixmap pixmap, QWidget *parent) :
    ABaseWidget(parent) {
    setStyleSheet("background-color:transparent; border:none");
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    // 创建 QGraphicsView 和 QGraphicsScene
    QGraphicsView *view = new QGraphicsView(this);
    QGraphicsScene *scene = new QGraphicsScene(this);

    m_RotatingPixmapItem = new ARotatingPixmapItem(pixmap);

    scene->addItem(m_RotatingPixmapItem);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(pixmap.width(), pixmap.height());

    // 将 QGraphicsView 添加到布局中
    layout->addWidget(view);

    // 设置场景
    view->setScene(scene);
}

AWidgetWithRotatingItem::AWidgetWithRotatingItem(QWidget *parent)  :
    AWidgetWithRotatingItem(QPixmap(":agui/res/image/loading-48.png"), parent) {
}

void AWidgetWithRotatingItem::start() {
    // 启动动画
    m_RotatingPixmapItem->start();
}

void AWidgetWithRotatingItem::stop() {
    // 停止动画
    m_RotatingPixmapItem->stop();
}
