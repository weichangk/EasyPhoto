/*
 * @Author: weick
 * @Date: 2023-12-05 23:02:37
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-08 23:15:44
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

    enum Funcs {
        ImageConversion = 0, // 图片转换
        ImageCompression,    // 图片压缩
        ImageCropping,       // 图片裁剪
        ImageAmplification,  // 图像放大
        ImageManipulation,   // 图片抠像
        ImageErase,          // 图片擦除
        ImageEnhancement,    // 图像增强
        ImageRestoration,    // 图像复原
        ImageEffect,         // 图片效果
        ImageSpecialEffect   // 图片特效
    };
    Q_ENUM(Funcs)

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
