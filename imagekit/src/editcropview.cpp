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

void EditCropView::resizeEvent(QResizeEvent *event) {
    ABaseWidget::resizeEvent(event);
    selectionRect = QRect(0, 0, width(), height());
    updateAnchors();
}

void EditCropView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    painter.fillRect(rect(), QColor(0, 0, 0, 1));

    // 绘制选框
    painter.setPen(Qt::red);
    painter.drawRect(selectionRect);

    // 绘制锚点
    painter.setBrush(Qt::red);
    for (int i = 0; i < 8; ++i) {
        QRect anchorRect = QRect(anchorPoints[i].x() - anchorSize / 2, anchorPoints[i].y() - anchorSize / 2,
                                 anchorSize, anchorSize);
        painter.drawRect(anchorRect);
    }
}

void EditCropView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // 检查是否点击了锚点
        for (int i = 0; i < 8; ++i) {
            QRect anchorRect = QRect(anchorPoints[i].x() - anchorSize / 2, anchorPoints[i].y() - anchorSize / 2,
                                     anchorSize, anchorSize);
            if (anchorRect.contains(event->pos())) {
                resizing = true;
                resizeMode = i;
                return;
            }
        }

        // 检查是否点击了选框内部
        if (selectionRect.contains(event->pos())) {
            moving = true;
            lastPos = event->pos();
            return;
        }
    }
}

void EditCropView::mouseMoveEvent(QMouseEvent *event) {
    if (resizing) {
        // 调整选框大小
        resizeSelectionSize(event->pos());
        return;
    }

    if (moving) {
        // 移动选框
        moveSelection(event->pos());
        return;
    }

    // 更新鼠标样式
    updateCursor(event->pos());
}

void EditCropView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        resizing = false;
        moving = false;
    }
}

void EditCropView::resizeSelectionSize(const QPoint &pos) {
    QPoint newPos = pos;
    QPoint center = anchorPoints[resizeMode];
    switch (resizeMode) {
    case 0: // 左上角
        if(anchorPoints[4].x() - min_width_ < newPos.x()) {
            newPos.setX(anchorPoints[4].x() - min_width_);
        }
        if(anchorPoints[4].y() - min_height_ < newPos.y()) {
            newPos.setY(anchorPoints[4].y() - min_height_);
        }
        if(newPos.x() < 0) {
            newPos.setX(0);
        }
        if(newPos.y() < 0) {
            newPos.setY(0);
        }
        selectionRect.setTopLeft(newPos);
        break;
    case 1: // 上边
        if(anchorPoints[5].y() - min_height_ < newPos.y()) {
            newPos.setY(anchorPoints[5].y() - min_height_);
        }
        if(newPos.y() < 0) {
            newPos.setY(0);
        }
        selectionRect.setTop(newPos.y());
        break;
    case 2: // 右上角
        if(min_width_ + anchorPoints[6].x() > newPos.x()) {
            newPos.setX(min_width_ + anchorPoints[6].x());
        }
        if(anchorPoints[6].y() - min_height_ < newPos.y()) {
            newPos.setY(anchorPoints[6].y() - min_height_);
        }
        if(newPos.x() > width()) {
            newPos.setX(width());
        }
        if(newPos.y() < 0) {
            newPos.setY(0);
        }
        selectionRect.setTopRight(newPos);
        break;
    case 3: // 右边
        if(min_width_ + anchorPoints[7].x() > newPos.x()) {
            newPos.setX(min_width_ + anchorPoints[7].x());
        }
        if(newPos.x() > width()) {
            newPos.setX(width());
        }
        selectionRect.setRight(newPos.x());
        break;
    case 4: // 右下角
        if(min_width_ + anchorPoints[0].x() > newPos.x()) {
            newPos.setX(min_width_ + anchorPoints[0].x());
        }
        if(min_height_ + anchorPoints[0].y() > newPos.y()) {
            newPos.setY(min_height_ + anchorPoints[0].y());
        }
        if(newPos.x() > width()) {
            newPos.setX(width());
        }
        if(newPos.y() > height()) {
            newPos.setY(height());
        }
        selectionRect.setBottomRight(newPos);
        break;
    case 5: // 下边
        if(min_height_ + anchorPoints[1].y() > newPos.y()) {
            newPos.setY(min_height_ + anchorPoints[0].y());
        }
        if(newPos.y() > height()) {
            newPos.setY(height());
        }
        selectionRect.setBottom(newPos.y());
        break;
    case 6: // 左下角
        if(anchorPoints[2].x() - min_width_ < newPos.x()) {
            newPos.setX(anchorPoints[2].x() - min_width_);
        }
        if(min_height_ + anchorPoints[2].y() > newPos.y()) {
            newPos.setY(min_height_ + anchorPoints[2].y());
        }
        if(newPos.x() < 0) {
            newPos.setX(0);
        }
        if(newPos.y() > height()) {
            newPos.setY(height());
        }
        selectionRect.setBottomLeft(newPos);
        break;
    case 7: // 左边
        if(anchorPoints[3].x() - min_width_ < newPos.x()) {
            newPos.setX(anchorPoints[3].x() - min_width_);
        }
        if(newPos.x() < 0) {
            newPos.setX(0);
        }
        selectionRect.setLeft(newPos.x());
        break;
    }

    anchorPoints[resizeMode] = center;
    updateAnchors();
    update();
}

void EditCropView::moveSelection(const QPoint &pos) {
    QPoint delta = pos - lastPos;
    if(delta.x() < 0 && selectionRect.left() + delta.x() < 0) {
        delta.setX(selectionRect.left());
    }
    if(delta.y() < 0 && selectionRect.top() + delta.y() < 0) {
        delta.setY(selectionRect.top());
    }
    if(delta.x() > 0 && selectionRect.right() + delta.x() > width()) {
        delta.setX(width() - selectionRect.right());
    }
    if(delta.y() > 0 && selectionRect.bottom() + delta.y() > height()) {
        delta.setY(height() - selectionRect.bottom());
    }
    selectionRect.translate(delta);
    updateAnchors();
    update();
    lastPos = pos;
}

void EditCropView::updateAnchors() {
    QRect rect = selectionRect;
    anchorPoints[0] = rect.topLeft();
    anchorPoints[1] = QPoint(rect.center().x(), rect.top());
    anchorPoints[2] = rect.topRight();
    anchorPoints[3] = QPoint(rect.right(), rect.center().y());
    anchorPoints[4] = rect.bottomRight();
    anchorPoints[5] = QPoint(rect.center().x(), rect.bottom());
    anchorPoints[6] = rect.bottomLeft();
    anchorPoints[7] = QPoint(rect.left(), rect.center().y());
}

void EditCropView::updateCursor(const QPoint &pos) {
    for (int i = 0; i < 8; ++i) {
        if (QRect(anchorPoints[i].x() - anchorSize / 2, anchorPoints[i].y() - anchorSize / 2,
                  anchorSize, anchorSize)
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
            return;
        }
    }

    setCursor(Qt::ArrowCursor);
}
} // namespace imageedit