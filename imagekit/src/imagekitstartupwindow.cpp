#include "inc/imagekitstartupwindow.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/acanmovewidget.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ashadoweffect.h"
#include "../awidget/inc/apushbutton.h"
#include "inc/imagefuncview.h"
#include "inc/imagefuncmodel.h"
#include "inc/imagefuncdelegate.h"
#include <QPainter>
#include <QPainterPath>

ImageKitStartupWindow::ImageKitStartupWindow(QWidget *parent) : ABaseWidget(parent)
{
    createUi();
    sigConnect();
    changeLanguage();
}

ImageKitStartupWindow::~ImageKitStartupWindow()
{
}

void ImageKitStartupWindow::createUi()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(800, 540);

    auto mainLayout = new AHBoxLayout(this);

    auto leftLayout = new AVBoxLayout();
    mainLayout->addLayout(leftLayout);

    auto rightLayout = new AVBoxLayout();
    mainLayout->addLayout(rightLayout);

    //left
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
    m_LogoBtn->setObjectName("m_LogoBtn");
    m_LogoBtn->setFixedSize(32, 32);
    logoLayout->addWidget(m_LogoBtn);

    auto vipLayout = new AVBoxLayout();
    vipLayout->setSpacing(3);
    logoLayout->addLayout(vipLayout);

    m_VipBtn = new APushButton(m_Navbar);
    m_VipBtn->setObjectName("m_VipBtn");
    m_VipBtn->setFixedHeight(16);
    vipLayout->addWidget(m_VipBtn);

    m_VipRightsBtn = new APushButton(m_Navbar);
    m_VipRightsBtn->setObjectName("m_VipRightsBtn");
    m_VipRightsBtn->setFixedHeight(16);
    vipLayout->addWidget(m_VipRightsBtn);

    navbarLayout->addSpacing(20);

    m_FuncBtn = new APushButton(m_Navbar);
    m_FuncBtn->setObjectName("m_FuncBtn");
    m_FuncBtn->setFixedHeight(32);
    navbarLayout->addWidget(m_FuncBtn);

    m_FilesBtn = new APushButton(m_Navbar);
    m_FilesBtn->setObjectName("m_FilesBtn");
    m_FilesBtn->setFixedHeight(32);
    navbarLayout->addWidget(m_FilesBtn);

    m_SettingsBtn = new APushButton(m_Navbar);
    m_SettingsBtn->setObjectName("m_SettingsBtn");
    m_SettingsBtn->setFixedHeight(32);
    navbarLayout->addWidget(m_SettingsBtn);

    navbarLayout->addStretch();

    //right
    m_Topbar = new ATopbar(this);
    m_Topbar->setCloseBtnTopRight10Radius();
    rightLayout->addWidget(m_Topbar);

    auto funcLayout = new AHBoxLayout();
    funcLayout->setContentsMargins(0, 0, 1, 1);
    rightLayout->addLayout(funcLayout, 1);

    m_FuncArea = new AWidget(this);
    m_FuncArea->setObjectName("ImageKitStartupWindow_m_FuncArea");
    funcLayout->addWidget(m_FuncArea, 1);

    auto funcAreaLayout = new AHBoxLayout(m_FuncArea);
    funcAreaLayout->setContentsMargins(20, 20, 20, 20);

    ImageFuncModel *imageFuncModel = new ImageFuncModel;
    ImageFuncDelegate *imageFuncDelegate = new ImageFuncDelegate;
    m_ImageFuncView = new ImageFuncView(this);
    m_ImageFuncView->setModel(imageFuncModel);
    m_ImageFuncView->setItemDelegate(imageFuncDelegate);
    funcAreaLayout->addWidget(m_ImageFuncView, 1);

    auto shadow = new AShadowEffect(this);
}

void ImageKitStartupWindow::changeLanguage()
{
}

void ImageKitStartupWindow::sigConnect()
{
    connect(m_Topbar, &ATopbar::sigMin, this, [=]()
            { showMinimized(); });
    connect(m_Topbar, &ATopbar::sigMax, this, [=]()
            { showMaximized(); });
    connect(m_Topbar, &ATopbar::sigNormal, this, [=]()
            { showNormal(); });
    connect(m_Topbar, &ATopbar::sigClose, this, [=]()
            { close(); });
}

void ImageKitStartupWindow::paintEvent(QPaintEvent *event)
{
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
