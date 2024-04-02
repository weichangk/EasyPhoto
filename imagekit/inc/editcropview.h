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
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool selecting_ = false;
    QPoint start_point_;
    QPoint end_point_;
};
} // namespace imageedit