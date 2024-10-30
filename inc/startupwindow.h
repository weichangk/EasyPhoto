#pragma once
#include "component/navbarwidget.h"
#include "component/topbarwidget.h"
#include "component/canmovewidget.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>

class StartupWindow : public QWidget {
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
    void createUi();
    void sigConnect();
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    void slotNavClicked(QString objectName);

private:
    TopbarWidget *m_Topbar = 0;
    CanMoveWidget *m_Navbar = 0;
    QWidget *m_FuncArea = 0;

    QPushButton *m_LogoBtn = 0;
    QPushButton *m_VipBtn = 0;
    QPushButton *m_VipRightsBtn = 0;

    NavbarWidget *m_Navbarwidget = 0;
};
