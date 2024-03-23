/*
 * @Author: weick
 * @Date: 2023-12-05 23:04:11
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-10 14:40:01
 */

#include "inc/startupwindow.h"
#include "inc/models.h"
#include "inc/signals.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/aflowlayout.h"
#include "../awidget/inc/ashadoweffect.h"
#include "../agui/inc/afuncpanelwidget.h"
#include <QPainter>
#include <QPainterPath>

using Funcs = Models::Funcs;

StartupWindow::StartupWindow(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

StartupWindow::~StartupWindow() {
}

void StartupWindow::createUi() {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(800, 540);

    auto mainLayout = new AHBoxLayout(this);

    auto leftLayout = new AVBoxLayout();
    mainLayout->addLayout(leftLayout);

    auto rightLayout = new AVBoxLayout();
    mainLayout->addLayout(rightLayout);

    // left
    m_Navbar = new ACanMoveWidget(this);
    m_Navbar->setFixedWidth(140);
    leftLayout->addWidget(m_Navbar, 1);

    auto navbarLayout = new AVBoxLayout(m_Navbar);
    navbarLayout->setContentsMargins(12, 24, 12, 24);
    navbarLayout->setSpacing(10);

    auto logoLayout = new AHBoxLayout();
    logoLayout->setSpacing(6);
    navbarLayout->addLayout(logoLayout);

    m_LogoBtn = new APushButton(m_Navbar);
    m_LogoBtn->setObjectName("StartupWindow_m_LogoBtn");
    m_LogoBtn->setFixedSize(40, 40);
    logoLayout->addWidget(m_LogoBtn);

    auto vipLayout = new AVBoxLayout();
    logoLayout->addLayout(vipLayout);

    m_VipBtn = new APushButton(m_Navbar);
    m_VipBtn->setObjectName("StartupWindow_m_VipBtn");
    m_VipBtn->setText("登录");
    vipLayout->addWidget(m_VipBtn);

    m_VipRightsBtn = new APushButton(m_Navbar);
    m_VipRightsBtn->setObjectName("StartupWindow_m_VipRightsBtn");
    m_VipRightsBtn->setText("会员特惠");
    vipLayout->addWidget(m_VipRightsBtn);

    navbarLayout->addSpacing(20);

    QMap<int, QVariantList> navbarDataMap;
    navbarDataMap.insert(StartupNav::MyFunc, QVariantList() << ":/res/image/icon24_menu_myfuncs.png"
                                                            << "全部功能");
    navbarDataMap.insert(StartupNav::MyFiles, QVariantList() << ":/res/image/icon24_menu_myfiles.png"
                                                             << "我的文件");
    navbarDataMap.insert(StartupNav::MySettings, QVariantList() << ":/res/image/icon24_menu_mysettings.png"
                                                                << "设置");
    m_Navbarwidget = new ANavbarWidget(navbarDataMap, this);
    navbarLayout->addWidget(m_Navbarwidget);

    navbarLayout->addStretch();

    // right
    m_Topbar = new ATopbar(this);
    m_Topbar->setCloseBtnTopRight10Radius();
    rightLayout->addWidget(m_Topbar);

    auto funcLayout = new AVBoxLayout();
    funcLayout->setContentsMargins(0, 0, 1, 1);
    rightLayout->addLayout(funcLayout);

    m_FuncArea = new AWidget(this);
    m_FuncArea->setObjectName("StartupWindow_m_FuncArea");
    funcLayout->addWidget(m_FuncArea);

    auto funcFlowLayout = new AFlowLayout(m_FuncArea, 20, 12, 12);
    QMap<int, QVariantList> funcDataMap;
    funcDataMap.insert(Funcs::ImageConversion, QVariantList() << ":/res/image/account_80_vip.png"
                                                              << "图片转换"
                                                              << "支持多种格式转换");
    funcDataMap.insert(Funcs::ImageCompression, QVariantList() << ":/res/image/account_80_vip.png"
                                                               << "图片压缩"
                                                               << "高质量压缩图片");
    funcDataMap.insert(Funcs::ImageCropping, QVariantList() << ":/res/image/account_80_vip.png"
                                                            << "图片编辑"
                                                            << "裁剪、旋转、饱和度、水印");
    funcDataMap.insert(Funcs::ImageSpecialEffect, QVariantList() << ":/res/image/account_80_vip.png"
                                                         << "GIF生产"
                                                         << "图片生成GIF");
    funcDataMap.insert(Funcs::ImageEnhancement, QVariantList() << ":/res/image/account_80_vip.png"
                                                               << "AI图像增强"
                                                               << "图片画质增强");
    funcDataMap.insert(Funcs::ImageErase, QVariantList() << ":/res/image/account_80_vip.png"
                                                         << "AI图片擦除"
                                                         << "去除图片水印");
    // funcDataMap.insert(Funcs::ImageErase, QVariantList() << ":/res/image/account_80_vip.png"
    //                                                      << "图像修复"
    //                                                      << "老旧照片修复");
    // funcDataMap.insert(Funcs::ImageManipulation, QVariantList() << ":/res/image/account_80_vip.png"
    //                                                             << "AI抠像"
    //                                                             << "去除图片背景");
    // funcDataMap.insert(Funcs::ImageSpecialEffect, QVariantList() << ":/res/image/account_80_vip.png"
    //                                                              << "图片特效"
    //                                                              << "支持多种图片特效");
    QMap<int, QVariantList>::Iterator iter;
    for (iter = funcDataMap.begin(); iter != funcDataMap.end(); ++iter) {
        auto btn = new AFuncPanelWidget(this, iter.key());
        btn->setFixedSize(198, 90);
        btn->getLayout()->setContentsMargins(24, 24, 24, 24);
        btn->getIcon()->setPixmap(QPixmap(iter.value().at(0).toString()));
        btn->getIcon()->setScaledContents(true);
        btn->getName()->setText(iter.value().at(1).toString());
        btn->getDec()->setText(iter.value().at(2).toString());
        connect(btn, &AFuncPanelWidget::sigClicked, this, [=](int id) {
            emit Signals::getInstance()->sigGotoFunc((Models::Funcs)id);
        });
        funcFlowLayout->addWidget(btn);
    }

    auto shadow = new AShadowEffect(this);
}

void StartupWindow::changeLanguage() {
}

void StartupWindow::sigConnect() {
    connect(m_Topbar, &ATopbar::sigMin, this, [=]() { showMinimized(); });
    connect(m_Topbar, &ATopbar::sigMax, this, [=]() { showMaximized(); });
    connect(m_Topbar, &ATopbar::sigNormal, this, [=]() { showNormal(); });
    connect(m_Topbar, &ATopbar::sigClose, this, [=]() { close(); });
}

void StartupWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 背景色透明
    painter.fillRect(this->rect(), QColor(0, 0, 0, 1));

    // 背景图
    QPixmap pixmapTemp = QPixmap(this->rect().size());
    pixmapTemp.fill(QColor("#181818"));
    pixmapTemp.setDevicePixelRatio(1);

    // 背景图圆角裁剪
    QPainterPath path;
    path.addRoundedRect(this->rect(), 10, 10);
    painter.setClipPath(path);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(this->rect(), pixmapTemp);

    // 边框
    QPen pen(QColor("#402F38"));
    pen.setWidth(1);
    painter.setPen(pen);
    auto borderRect = this->rect(); //.adjusted(1, 1, -1, -1);
    painter.drawRoundedRect(borderRect, 10, 10);
}

void StartupWindow::showEvent(QShowEvent *event) {
    ABaseWidget::showEvent(event);
    // AFlowLayout会撑大设置setMinimumSize的窗体，暂时这样解决
    resize(800, 540);
}

void StartupWindow::slotNavClicked(QString objectName) {
    if ("m_FuncBtn" == objectName) {
    } else if ("m_FilesBtn" == objectName) {
    } else if ("m_SettingsBtn" == objectName) {
    }
}
