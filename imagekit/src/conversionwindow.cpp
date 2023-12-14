/*
 * @Author: weick
 * @Date: 2023-12-09 22:47:15
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-14 00:04:49
 */

#include "inc/conversionwindow.h"
#include "inc/conversionmodels.h"
#include "inc/signals.h"
#include "inc/models.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ashadoweffect.h"
#include <QPainter>
#include <QPainterPath>

ConversionWindow::ConversionWindow(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

ConversionWindow::~ConversionWindow() {
}

void ConversionWindow::createUi() {
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
    m_LogoBtn->setObjectName("ConversionWindow_m_LogoBtn");
    m_LogoBtn->setFixedSize(40, 40);
    logoLayout->addWidget(m_LogoBtn);

    m_ProductLab = new ALabel(m_Navbar);
    m_ProductLab->setObjectName("ConversionWindow_m_ProductLab");
    m_ProductLab->setText("图片转换");
    logoLayout->addWidget(m_ProductLab);

    navbarLayout->addSpacing(20);

    QMap<int, QVariantList> navbarDataMap;
    navbarDataMap.insert(ConvertOutType::PNG, QVariantList() << ":/res/image/icon24_menu_myfuncs.png"
                                                             << "转换为PNG");
    navbarDataMap.insert(ConvertOutType::JPG, QVariantList() << ":/res/image/icon24_menu_myfiles.png"
                                                             << "转换为JPG");
    navbarDataMap.insert(ConvertOutType::JPEG, QVariantList() << ":/res/image/icon24_menu_mysettings.png"
                                                              << "转换为JPEG");
    navbarDataMap.insert(ConvertOutType::SVG, QVariantList() << ":/res/image/icon24_menu_mysettings.png"
                                                             << "转换为SVG");
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

    auto convertArea = new AWidget(this);
    convertArea->setObjectName("ConversionWindow_m_FuncArea");
    funcLayout->addWidget(convertArea);

    auto convertListViewLayout = new AVBoxLayout(convertArea);
    // convertListViewLayout->setContentsMargins(24 , 24, 24, 24);

    m_ConversionListView = new ConversionListView(this);
    convertListViewLayout->addWidget(m_ConversionListView);

    QList<ConversionData> conversionDatas;
    ConversionData data1 ={true, "", "", ConversionModels::ConversionType::None, QPixmap(":/res/image/icons8-add-image-96.png")};
    ConversionData data2 ={false, "", "", ConversionModels::ConversionType::None, QPixmap()};
    conversionDatas.append(data1);
    m_ConversionListView->chageData(conversionDatas);

    auto shadow = new AShadowEffect(this);
}

void ConversionWindow::changeLanguage() {
}

void ConversionWindow::sigConnect() {
    connect(m_Topbar, &ATopbar::sigMin, this, [=]() { showMinimized(); });
    connect(m_Topbar, &ATopbar::sigMax, this, [=]() { showMaximized(); });
    connect(m_Topbar, &ATopbar::sigNormal, this, [=]() { showNormal(); });
    connect(m_Topbar, &ATopbar::sigClose, this, [=]() {
        close();
        emit Signals::getInstance()->sigGotoFunc(Models::Funcs::Startup);
    });
}

void ConversionWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 背景色透明
    painter.fillRect(this->rect(), QColor(0, 0, 0, 1));

    // 背景图
    QPixmap pixmapTemp = QPixmap(this->rect().size());
    pixmapTemp.fill(QColor(32, 32, 32, 255));
    pixmapTemp.setDevicePixelRatio(1);

    // 背景图圆角裁剪
    QPainterPath path;
    path.addRoundedRect(this->rect(), 10, 10);
    painter.setClipPath(path);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(this->rect(), pixmapTemp);

    // 边框
    QPen pen(QColor(96, 96, 96, 255));
    pen.setWidth(1);
    painter.setPen(pen);
    auto borderRect = this->rect(); //.adjusted(1, 1, -1, -1);
    painter.drawRoundedRect(borderRect, 10, 10);
}
