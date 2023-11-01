#include "inc/imagekitstartupview.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/acanmovewidget.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ashadoweffect.h"
#include <QPainter>
#include <QPainterPath>

ImageKitStartupView::ImageKitStartupView(QWidget *parent) : ABaseWidget(parent)
{
    createUi();
    sigConnect();
    changeLanguage();
}

ImageKitStartupView::~ImageKitStartupView()
{
}

void ImageKitStartupView::createUi()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(800, 540);

    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    m_Navbar = new ACanMoveWidget(this);
    m_Navbar->setFixedWidth(140);

    mainLayout->addWidget(m_Navbar);

    auto rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(0);

    mainLayout->addLayout(rightLayout);

    m_Topbar = new ATopbar(this);
    m_Topbar->setCloseBtnTopRight10Radius();
    rightLayout->addWidget(m_Topbar);

    m_FuncArea = new AWidget(this);
    m_FuncArea->setObjectName("ImageKitStartupView_m_FuncArea");
    auto funcLayout = new AHBoxLayout();
    funcLayout->setContentsMargins(0, 0, 1, 1);
    funcLayout->setSpacing(0);
    funcLayout->addWidget(m_FuncArea, 1);
    rightLayout->addLayout(funcLayout, 1);
    // rightLayout->addStretch();

    auto shadow = new AShadowEffect(this);
}

void ImageKitStartupView::changeLanguage()
{
}

void ImageKitStartupView::sigConnect()
{
}

void ImageKitStartupView::paintEvent(QPaintEvent *event)
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
