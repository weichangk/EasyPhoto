/*
 * @Author: weick
 * @Date: 2023-12-05 23:02:37
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:02:37
 */

#pragma once
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/anavbarwidget.h"
#include <QButtonGroup>

class ATopbar;
class ACanMoveWidget;
class APushButton;
class ImageFuncView;
class ImageFuncModel;
class ImageFuncDelegate;
class ImageFunc;
class StartupWindow : public ABaseWidget {
    Q_OBJECT
public:
    enum StartupNav {
        MyFunc = 0,
        MyFiles,
        MySettings
    };
    Q_ENUM(StartupNav)

    StartupWindow(QWidget *parent = nullptr);
    ~StartupWindow();
    void imageFuncModelAppend(QList<ImageFunc *> funcs);

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
    void paintEvent(QPaintEvent *event) override;

private:
    void slotNavClicked(QString objectName);

private:
    ATopbar *m_Topbar = nullptr;
    ACanMoveWidget *m_Navbar = nullptr;
    AWidget *m_FuncArea = nullptr;

    APushButton *m_LogoBtn = nullptr;
    APushButton *m_VipBtn = nullptr;
    APushButton *m_VipRightsBtn = nullptr;

    ANavbarWidget *m_anavbarwidget = nullptr;

    ImageFuncView *m_ImageFuncView = nullptr;
    ImageFuncModel *m_ImageFuncModel = nullptr;
    ImageFuncDelegate *m_ImageFuncDelegate = nullptr;
};
