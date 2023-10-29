#include "inc/imagekitstartupview.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/acanmovewidget.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"

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
    rightLayout->addWidget(m_Topbar);
    rightLayout->addStretch();

}

void ImageKitStartupView::changeLanguage()
{
}

void ImageKitStartupView::sigConnect()
{
}
