/*
 * @Author: weick
 * @Date: 2023-12-05 23:02:37
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-09 23:54:28
 */

#pragma once
#include "../awidget/inc/apushbutton.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/anavbarwidget.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/acanmovewidget.h"
#include <QButtonGroup>

class StartupWindow : public ABaseWidget {
    Q_OBJECT
public:
    enum StartupNav {
        MyFunc = 0,
        MyFiles,
        MySettings
    };
    Q_ENUM(StartupNav)

    StartupWindow(QWidget *parent = 0);
    ~StartupWindow();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    void slotNavClicked(QString objectName);

private:
    ATopbar *m_Topbar = 0;
    ACanMoveWidget *m_Navbar = 0;
    AWidget *m_FuncArea = 0;

    APushButton *m_LogoBtn = 0;
    APushButton *m_VipBtn = 0;
    APushButton *m_VipRightsBtn = 0;

    ANavbarWidget *m_Navbarwidget = 0;
};
