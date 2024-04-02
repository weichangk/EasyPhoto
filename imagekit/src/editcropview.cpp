/*
 * @Author: weick
 * @Date: 2024-04-02 07:32:51
 * @Last Modified by: weick
 * @Last Modified time: 2024-04-02 07:52:42
 */

#include "inc/editcropview.h"
#include <QPainter>
#include <QMouseEvent>

namespace imageedit {
EditCropView::EditCropView(QWidget *parent) :
    ABaseWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setMouseTracking(true);
}
EditCropView::~EditCropView() {
}
void EditCropView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 0, 1));

    if (selecting_) {
        painter.setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter.drawRect(QRect(start_point_, end_point_));
    }
}
void EditCropView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        selecting_ = true;
        start_point_ = event->pos();
        end_point_ = start_point_;
        update();
    }
}
void EditCropView::mouseMoveEvent(QMouseEvent *event) {
    if (selecting_) {
        end_point_ = event->pos();
        update();
    }
}
void EditCropView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        selecting_ = false;
        setMask(QRegion(QRect(start_point_, end_point_)));
        update();
    }
}
} // namespace imageedit