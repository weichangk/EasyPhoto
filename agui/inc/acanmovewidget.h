/*
 * @Author: weick
 * @Date: 2023-12-05 22:51:20
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 22:51:20
 */

#pragma once
#include "agui_global.h"
#include "abasewidget.h"

class AGUI_EXPORT ACanMoveWidget : public ABaseWidget {
    Q_OBJECT
public:
    ACanMoveWidget(QWidget *parent);
    ~ACanMoveWidget();
    void canMoveEnabled(bool enabled) {
        m_canMoveEnabled = enabled;
    }

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QWidget *m_parentWidget;
    bool m_canMoveEnabled = true;
    bool m_isMousePressed;
    QPoint m_lastMousePos;
    QRect m_pressRect;
};
