/*
 * @Author: weick
 * @Date: 2024-04-02 07:32:51
 * @Last Modified by: weick
 * @Last Modified time: 2024-04-02 07:52:42
 */

#include "inc/editcropview.h"
#include "inc/models.h"
#include <QPainter>
#include <QMouseEvent>

namespace imageedit {
EditCropView::EditCropView(QWidget *parent) :
    ABaseWidget(parent), min_width_(kCropRectMinW), min_height_(kCropRectMinH) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);
}

EditCropView::~EditCropView() {
}

void EditCropView::setSelectionRect(const QRect &rect) {
    selection_rect_ = rect;
    updateAnchors();
    update();
}

void EditCropView::setAspectRatio(double aspectRatio) {
    aspect_ratio_ = aspectRatio;
}

void EditCropView::setUseAspectRatio(bool use) {
    use_aspect_ratio_ = use;
}

void EditCropView::resizeEvent(QResizeEvent *event) {
    ABaseWidget::resizeEvent(event);
}

void EditCropView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    painter.fillRect(rect(), QColor(0, 0, 0, 1));

    // 绘制选框
    painter.setPen(Qt::red);
    painter.drawRect(selection_rect_);

    // 绘制锚点
    painter.setBrush(Qt::red);
    for (int i = 0; i < 8; ++i) {
        QRect anchorRect = QRect(anchor_points_[i].x() - anchor_size_ / 2, anchor_points_[i].y() - anchor_size_ / 2,
                                 anchor_size_, anchor_size_);
        painter.drawRect(anchorRect);
    }
}

void EditCropView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // 检查是否点击了锚点
        for (int i = 0; i < 8; ++i) {
            QRect anchorRect = QRect(anchor_points_[i].x() - anchor_size_ / 2, anchor_points_[i].y() - anchor_size_ / 2,
                                     anchor_size_, anchor_size_);
            if (anchorRect.contains(event->pos())) {
                resizing_ = true;
                resize_mode_ = i;
                return;
            }
        }

        // 检查是否点击了选框内部
        if (selection_rect_.contains(event->pos())) {
            moving_ = true;
            last_pos_ = event->pos();
            return;
        }
    }
}

void EditCropView::mouseMoveEvent(QMouseEvent *event) {
    if (resizing_) {
        // 调整选框大小
        if (use_aspect_ratio_) {
            resizeSelectionSizeUseAspectRatio(event->pos());
        } else {
            resizeSelectionSize(event->pos());
        }
        return;
    }

    if (moving_) {
        // 移动选框
        moveSelection(event->pos());
        return;
    }

    // 更新鼠标样式
    updateCursor(event->pos());
}

void EditCropView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        resizing_ = false;
        moving_ = false;
        emit sigSelectRectChangedEnd(selection_rect_);
    }
}

void EditCropView::resizeSelectionSize(const QPoint &pos) {
    QPoint newPos = pos;
    QPoint center = anchor_points_[resize_mode_];
    switch (resize_mode_) {
    case 0: // 左上角
        if(anchor_points_[4].x() - min_width_ < newPos.x()) {
            newPos.setX(anchor_points_[4].x() - min_width_);
        }
        if(anchor_points_[4].y() - min_height_ < newPos.y()) {
            newPos.setY(anchor_points_[4].y() - min_height_);
        }
        if(newPos.x() < 0) {
            newPos.setX(0);
        }
        if(newPos.y() < 0) {
            newPos.setY(0);
        }
        selection_rect_.setTopLeft(newPos);
        break;
    case 1: // 上边
        if(anchor_points_[5].y() - min_height_ < newPos.y()) {
            newPos.setY(anchor_points_[5].y() - min_height_);
        }
        if(newPos.y() < 0) {
            newPos.setY(0);
        }
        selection_rect_.setTop(newPos.y());
        break;
    case 2: // 右上角
        if(min_width_ + anchor_points_[6].x() > newPos.x()) {
            newPos.setX(min_width_ + anchor_points_[6].x());
        }
        if(anchor_points_[6].y() - min_height_ < newPos.y()) {
            newPos.setY(anchor_points_[6].y() - min_height_);
        }
        if(newPos.x() > width()) {
            newPos.setX(width());
        }
        if(newPos.y() < 0) {
            newPos.setY(0);
        }
        selection_rect_.setTopRight(newPos);
        break;
    case 3: // 右边
        if(min_width_ + anchor_points_[7].x() > newPos.x()) {
            newPos.setX(min_width_ + anchor_points_[7].x());
        }
        if(newPos.x() > width()) {
            newPos.setX(width());
        }
        selection_rect_.setRight(newPos.x());
        break;
    case 4: // 右下角
        if(min_width_ + anchor_points_[0].x() > newPos.x()) {
            newPos.setX(min_width_ + anchor_points_[0].x());
        }
        if(min_height_ + anchor_points_[0].y() > newPos.y()) {
            newPos.setY(min_height_ + anchor_points_[0].y());
        }
        if(newPos.x() > width()) {
            newPos.setX(width());
        }
        if(newPos.y() > height()) {
            newPos.setY(height());
        }
        selection_rect_.setBottomRight(newPos);
        break;
    case 5: // 下边
        if(min_height_ + anchor_points_[1].y() > newPos.y()) {
            newPos.setY(min_height_ + anchor_points_[0].y());
        }
        if(newPos.y() > height()) {
            newPos.setY(height());
        }
        selection_rect_.setBottom(newPos.y());
        break;
    case 6: // 左下角
        if(anchor_points_[2].x() - min_width_ < newPos.x()) {
            newPos.setX(anchor_points_[2].x() - min_width_);
        }
        if(min_height_ + anchor_points_[2].y() > newPos.y()) {
            newPos.setY(min_height_ + anchor_points_[2].y());
        }
        if(newPos.x() < 0) {
            newPos.setX(0);
        }
        if(newPos.y() > height()) {
            newPos.setY(height());
        }
        selection_rect_.setBottomLeft(newPos);
        break;
    case 7: // 左边
        if(anchor_points_[3].x() - min_width_ < newPos.x()) {
            newPos.setX(anchor_points_[3].x() - min_width_);
        }
        if(newPos.x() < 0) {
            newPos.setX(0);
        }
        selection_rect_.setLeft(newPos.x());
        break;
    }

    anchor_points_[resize_mode_] = center;
    updateAnchors();
    update();
    emit sigSelectRectChanged(selection_rect_);
}

void EditCropView::resizeSelectionSizeUseAspectRatio(const QPoint &pos) {
    QPoint newPos = pos;
    QPoint center = anchor_points_[resize_mode_];
    switch (resize_mode_) {
    case 0: // 左上角
        if(anchor_points_[4].x() - min_width_ < newPos.x()) {
            newPos.setX(anchor_points_[4].x() - min_width_);
        }
        if(anchor_points_[4].y() - min_height_ < newPos.y()) {
            newPos.setY(anchor_points_[4].y() - min_height_);
        }
        if(newPos.x() < 0) {
            return;
        }
        if(newPos.y() < 0) {
            return;
        }
        selection_rect_.setTop(newPos.y());
        selection_rect_.setWidth(selection_rect_.height() * aspect_ratio_);
        break;
    case 1: // 上边
        if(anchor_points_[5].y() - min_height_ < newPos.y()) {
            newPos.setY(anchor_points_[5].y() - min_height_);
        }
        if(newPos.y() < 0) {
            return;
        }
        selection_rect_.setTop(newPos.y());
        selection_rect_.setWidth(selection_rect_.height() * aspect_ratio_);
        break;
    case 2: // 右上角
        if(min_width_ + anchor_points_[6].x() > newPos.x()) {
            newPos.setX(min_width_ + anchor_points_[6].x());
        }
        if(anchor_points_[6].y() - min_height_ < newPos.y()) {
            newPos.setY(anchor_points_[6].y() - min_height_);
        }
        if(newPos.x() > width()) {
            return;
        }
        if(newPos.y() < 0) {
            return;
        }
        selection_rect_.setTop(newPos.y());
        selection_rect_.setWidth(selection_rect_.height() * aspect_ratio_);
        break;
    case 3: // 右边
        if(min_width_ + anchor_points_[7].x() > newPos.x()) {
            newPos.setX(min_width_ + anchor_points_[7].x());
        }
        if(newPos.x() > width()) {
            return;
        }
        selection_rect_.setRight(newPos.x());
        selection_rect_.setHeight(selection_rect_.width() / aspect_ratio_);
        break;
    case 4: // 右下角
        if(min_width_ + anchor_points_[0].x() > newPos.x()) {
            newPos.setX(min_width_ + anchor_points_[0].x());
        }
        if(min_height_ + anchor_points_[0].y() > newPos.y()) {
            newPos.setY(min_height_ + anchor_points_[0].y());
        }
        if(newPos.x() > width()) {
            return;
        }
        if(newPos.y() > height()) {
            return;
        }
        selection_rect_.setRight(newPos.x());
        selection_rect_.setHeight(selection_rect_.width() / aspect_ratio_);

        break;
    case 5: // 下边
        if(min_height_ + anchor_points_[1].y() > newPos.y()) {
            newPos.setY(min_height_ + anchor_points_[0].y());
        }
        if(newPos.y() > height()) {
            return;
        }
        selection_rect_.setBottom(newPos.y());
        selection_rect_.setWidth(selection_rect_.height() * aspect_ratio_);
        break;
    case 6: // 左下角
        if(anchor_points_[2].x() - min_width_ < newPos.x()) {
            newPos.setX(anchor_points_[2].x() - min_width_);
        }
        if(min_height_ + anchor_points_[2].y() > newPos.y()) {
            newPos.setY(min_height_ + anchor_points_[2].y());
        }
        if(newPos.x() < 0) {
            return;
        }
        if(newPos.y() > height()) {
            return;
        }
        selection_rect_.setBottom(newPos.y());
        selection_rect_.setWidth(selection_rect_.height() * aspect_ratio_);
        break;
    case 7: // 左边
        if(anchor_points_[3].x() - min_width_ < newPos.x()) {
            newPos.setX(anchor_points_[3].x() - min_width_);
        }
        if(newPos.x() < 0) {
            return;
        }
        if(selection_rect_.y() + selection_rect_.height() == height()) {
            newPos.setX(selection_rect_.x());
            // return;
            
        }
        selection_rect_.setLeft(newPos.x());
        selection_rect_.setHeight(selection_rect_.width() / aspect_ratio_);
        break;
    }

    anchor_points_[resize_mode_] = center;
    updateAnchors();
    update();
    emit sigSelectRectChanged(selection_rect_);
}

void EditCropView::moveSelection(const QPoint &pos) {
    QPoint delta = pos - last_pos_;
    if(delta.x() < 0 && selection_rect_.left() + delta.x() < 0) {
        delta.setX(selection_rect_.left());
    }
    if(delta.y() < 0 && selection_rect_.top() + delta.y() < 0) {
        delta.setY(selection_rect_.top());
    }
    if(delta.x() > 0 && selection_rect_.right() + delta.x() > width()) {
        delta.setX(width() - selection_rect_.right());
    }
    if(delta.y() > 0 && selection_rect_.bottom() + delta.y() > height()) {
        delta.setY(height() - selection_rect_.bottom());
    }
    selection_rect_.translate(delta);
    updateAnchors();
    update();
    last_pos_ = pos;
    emit sigSelectRectChanged(selection_rect_);
}

void EditCropView::updateAnchors() {
    QRect rect = selection_rect_;
    anchor_points_[0] = rect.topLeft();
    anchor_points_[1] = QPoint(rect.center().x(), rect.top());
    anchor_points_[2] = rect.topRight();
    anchor_points_[3] = QPoint(rect.right(), rect.center().y());
    anchor_points_[4] = rect.bottomRight();
    anchor_points_[5] = QPoint(rect.center().x(), rect.bottom());
    anchor_points_[6] = rect.bottomLeft();
    anchor_points_[7] = QPoint(rect.left(), rect.center().y());
}

void EditCropView::updateCursor(const QPoint &pos) {
    if (selection_rect_.contains(pos)) {
        setCursor(Qt::SizeAllCursor);
        for (int i = 0; i < 8; ++i) {
            if (QRect(anchor_points_[i].x() - anchor_size_ / 2, anchor_points_[i].y() - anchor_size_ / 2,
                      anchor_size_, anchor_size_)
                    .contains(pos)) {
                switch (i) {
                case 0:
                case 4:
                    setCursor(Qt::SizeFDiagCursor);
                    break;
                case 1:
                case 5:
                    setCursor(Qt::SizeVerCursor);
                    break;
                case 2:
                case 6:
                    setCursor(Qt::SizeBDiagCursor);
                    break;
                case 3:
                case 7:
                    setCursor(Qt::SizeHorCursor);
                    break;
                }
            }
        }
    } else {
        setCursor(Qt::ArrowCursor);
    }
}
} // namespace imageedit