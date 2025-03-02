#include "mainview.h"
#include "message/titlebarfuncmessage.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

TitlebarView *MainView::titlebarView() const {
    return m_pTitlebarView;
}

NavbarView *MainView::navbarView() const {
    return m_pNavbarView;
}

FuncAreaView *MainView::funcAreaView() const {
    return m_pFuncAreaView;
}

void MainView::createUi() {
    setObjectName("MainView");
    setAttribute(Qt::WA_StyledBackground);
    setMinimumSize(1096, 680);
    setFixedSize(1096, 680);
    setWindowFlags(Qt::FramelessWindowHint);

    auto ShadowEffect = new ShadowPixmap(this);

    m_pTitlebarView = new TitlebarView(this);

    m_pNavbarView = new NavbarView(this);

    m_pFuncAreaView = new FuncAreaView(this);

    auto rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(0);
    rightLayout->addWidget(m_pTitlebarView);
    rightLayout->addWidget(m_pFuncAreaView);

    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_pNavbarView);
    layout->addLayout(rightLayout, 1);
}

void MainView::connectSig() {
}

void MainView::titlebarFuncHandle(ETitleBarFunc func) {
    switch (func) {
    case ETitleBarFunc::TitleBarFunc_Minimize:
        showMinimized();
        break;
    case ETitleBarFunc::TitleBarFunc_Maximize:
        showMaximized();
        break;
    case ETitleBarFunc::TitleBarFunc_Normal:
        showNormal();
        break;
    case ETitleBarFunc::TitleBarFunc_Close:
        close();
        break;
    }
}

bool MainView::handleMessage(IMessage *message) {
    if (TitlebarFuncMessage *msg = dynamic_cast<TitlebarFuncMessage *>(message)) {
        titlebarFuncHandle((ETitleBarFunc)msg->code());
    }
    return false;
}