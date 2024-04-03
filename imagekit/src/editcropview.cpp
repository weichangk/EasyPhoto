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
    QPoint center = anchorPoints[resizeMode];

    switch (resizeMode) {
    case 0: // 左上角
        selectionRect.setTopLeft(pos);
        break;
    case 1: // 上边
        selectionRect.setTop(pos.y());
        break;
    case 2: // 右上角
        selectionRect.setTopRight(pos);
        break;
    case 3: // 右边
        selectionRect.setRight(pos.x());
        break;
    case 4: // 右下角
        selectionRect.setBottomRight(pos);
        break;
    case 5: // 下边
        selectionRect.setBottom(pos.y());
        break;
    case 6: // 左下角
        selectionRect.setBottomLeft(pos);
        break;
    case 7: // 左边
        selectionRect.setLeft(pos.x());
        break;
    }

    anchorPoints[resizeMode] = center;
    updateAnchors();
    update();
}

void EditCropView::moveSelection(const QPoint &pos) {
    QPoint delta = pos - lastPos;
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