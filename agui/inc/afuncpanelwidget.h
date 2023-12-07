/*
 * @Author: weick
 * @Date: 2023-12-07 22:58:06
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-07 23:27:16
 */

#pragma once
#include "agui_global.h"
#include "abasewidget.h"
#include "../awidget/inc/alabel.h"

class AGUI_EXPORT AFuncPanelWidget : public ABaseWidget {
    Q_OBJECT
public:
    AFuncPanelWidget(QWidget *parent = 0);
    ~AFuncPanelWidget();
    void setIcon(QPixmap p);

Q_SIGNALS:
    void sigClicked();

protected:
    void createUi() override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    ALabel *m_Name = 0;
    ALabel *m_Dec = 0;
    ALabel *m_Icon = 0;
};
