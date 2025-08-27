#include "titlebarview.h"
#include "filter/movetitlebar.h"
#include "core/theme.h"
#include "message/titlebarfuncmessage.h"
#include "titlebarenum.h"

TitlebarView::TitlebarView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void TitlebarView::switchMaximizeBtn(bool bCurIsMaximize) {
    if (bCurIsMaximize) {
        m_pMaximizeBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_restore.svg").arg(QtmCore::Theme::currentTheme()));
    } else {
        m_pMaximizeBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_max.svg").arg(QtmCore::Theme::currentTheme()));
    }
}

void TitlebarView::createUi() {
    setObjectName("TitlebarView");
    setAttribute(Qt::WA_StyledBackground);
    setFixedHeight(48 - 12);

    m_pCloseBtn = new IconButton(this);
    m_pCloseBtn->setFixedSize(24, 24);
    m_pCloseBtn->setIconSize(24, 24);
    m_pCloseBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_CloseBlack.svg").arg(QtmCore::Theme::currentTheme()));
    m_pMaximizeBtn = new IconButton(this);
    m_pMaximizeBtn->setFixedSize(24, 24);
    m_pMaximizeBtn->setIconSize(24, 24);
    m_pMaximizeBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_max.svg").arg(QtmCore::Theme::currentTheme()));

    m_pMinimizeBtn = new IconButton(this);
    m_pMinimizeBtn->setFixedSize(24, 24);
    m_pMinimizeBtn->setIconSize(24, 24);
    m_pMinimizeBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_mini.svg").arg(QtmCore::Theme::currentTheme()));

    m_pMenuBtn = new IconButton(this);
    m_pMenuBtn->setFixedSize(24, 24);
    m_pMenuBtn->setIconSize(24, 24);
    m_pMenuBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_menu.svg").arg(QtmCore::Theme::currentTheme()));

    m_pSupportBtn = new IconButton(this);
    m_pSupportBtn->setFixedSize(24, 24);
    m_pSupportBtn->setIconSize(24, 24);
    m_pSupportBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_support.svg").arg(QtmCore::Theme::currentTheme()));

    m_pUserInfoBtn = new IconButton(this);
    m_pUserInfoBtn->setFixedSize(24, 24);
    m_pUserInfoBtn->setIconSize(24, 24);
    m_pUserInfoBtn->setNormalPixmapPath(QString(":/QtmImg/img/%1/v16/other/image48_avatar_free.svg").arg(QtmCore::Theme::currentTheme()));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(16, 12, 12, 0);
    layout->setSpacing(0);

    layout->addStretch();

    layout->addWidget(m_pBuyMemberBtn);
    layout->addSpacing(4);
    layout->addWidget(m_pUserInfoBtn);
    layout->addSpacing(18);
    layout->addWidget(m_pSupportBtn);
    layout->addSpacing(14);
    layout->addWidget(m_pMenuBtn);
    layout->addSpacing(14);
    layout->addWidget(m_pMinimizeBtn);
    layout->addSpacing(12);
    layout->addWidget(m_pMaximizeBtn);
    layout->addSpacing(12);
    layout->addWidget(m_pCloseBtn);

    m_pLang = new LanguageFilter(this);
    auto movefilter = new MoveTitleBar(this, this->parentWidget());
    movefilter->setFrameColor(QColor("#703eff"));
}

void TitlebarView::connectSig() {
    bool bIsConn = false;
    bIsConn = connect(m_pLang, &LanguageFilter::sigLanguageChange, this, &TitlebarView::slotLanguageChanged);
    Q_ASSERT(bIsConn);
    bIsConn = connect(m_pCloseBtn, &VectorButton::clicked, this, &TitlebarView::slotCloseBtnClicked);
    Q_ASSERT(bIsConn);
    bIsConn = connect(m_pMaximizeBtn, &VectorButton::clicked, this, &TitlebarView::slotMaximizeBtnClicked);
    Q_ASSERT(bIsConn);
    bIsConn = connect(m_pMinimizeBtn, &VectorButton::clicked, this, &TitlebarView::slotMinimizeBtnClicked);
    Q_ASSERT(bIsConn);
    bIsConn = connect(m_pMenuBtn, &VectorButton::clicked, this, &TitlebarView::slotMenuBtnClicked);
    Q_ASSERT(bIsConn);
    bIsConn = connect(m_pSupportBtn, &VectorButton::clicked, this, &TitlebarView::slotSupportBtnClicked);
    Q_ASSERT(bIsConn);
    bIsConn = connect(m_pUserInfoBtn, &VectorButton::clicked, this, &TitlebarView::slotUserInfoBtnClicked);
    Q_ASSERT(bIsConn);
}

QWidget *TitlebarView::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("TitlebarView_DividingLine");
    dividingLine->setFixedSize(1, 16);
    return dividingLine;
}

void TitlebarView::slotLanguageChanged() {
    m_pBuyMemberBtn->setText(tr("Buy Now"));
}

void TitlebarView::slotCloseBtnClicked() {
    TitlebarFuncMessage msg(ETitleBarFunc::TitleBarFunc_Close);
    presenter()->sendMessage(&msg);
}

void TitlebarView::slotMaximizeBtnClicked() {
    bool curIsMaximizeBtn = m_pMaximizeBtn->fourPixmapPath().contains("max");
    switchMaximizeBtn(curIsMaximizeBtn);
    TitlebarFuncMessage msg(curIsMaximizeBtn ? ETitleBarFunc::TitleBarFunc_Maximize : ETitleBarFunc::TitleBarFunc_Normal);
    presenter()->sendMessage(&msg);
}

void TitlebarView::slotMinimizeBtnClicked() {
    TitlebarFuncMessage msg(ETitleBarFunc::TitleBarFunc_Minimize);
    presenter()->sendMessage(&msg);
}

void TitlebarView::slotMenuBtnClicked() {
}

void TitlebarView::slotSupportBtnClicked() {
}

void TitlebarView::slotUserInfoBtnClicked() {
}

void TitlebarView::slotBuyMemberBtnClicked() {
}