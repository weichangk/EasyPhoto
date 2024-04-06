/*
 * @Author: weick
 * @Date: 2024-04-02 07:32:29
 * @Last Modified by: weick
 * @Last Modified time: 2024-04-02 07:47:18
 */

#pragma once
#include "../agui/inc/abasewidget.h"

namespace imageedit {
class EditCropView : public ABaseWidget {
public:
    EditCropView(QWidget *parent = nullptr);
    ~EditCropView();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void resizeSelectionSize(const QPoint &pos);
    void moveSelection(const QPoint &pos);
    void updateAnchors();
    void updateCursor(const QPoint &pos);

private:
    QRect selectionRect;
    bool resizing = false;
    bool moving = false;
    int resizeMode = 0;
    QPoint lastPos;
    QPoint anchorPoints[8];
    const int anchorSize = 6;
    const int min_width_ = 48;
    const int min_height_ = 48;
};
} // namespace imageedit