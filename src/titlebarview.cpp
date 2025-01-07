#include "titlebarview.h"
#include "filter/movetitlebar.h"

TitlebarView::TitlebarView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void TitlebarView::createUi() {
    setObjectName("TitlebarView");
    setAttribute(Qt::WA_StyledBackground);
    setFixedHeight(40);

    QFont iconFont = Font::getIconFont(":/font/iconfont.ttf");

    m_pCloseBtn = new VectorButton(this);
    m_pCloseBtn->setObjectName("VectorButton_HW28_I20");
    m_pCloseBtn->setFont(iconFont);
    m_pCloseBtn->setText(QChar(0xe634));

    m_pMaximizeBtn = new VectorButton(this);
    m_pMaximizeBtn->setObjectName("VectorButton_HW28_I20");
    m_pMaximizeBtn->setFont(iconFont);
    m_pMaximizeBtn->setText(QChar(0xe616));

    m_pMinimizeBtn = new VectorButton(this);
    m_pMinimizeBtn->setObjectName("VectorButton_HW28_I20");
    m_pMinimizeBtn->setFont(iconFont);
    m_pMinimizeBtn->setText(QChar(0xe604));

    m_pMenuBtn = new VectorButton(this);
    m_pMenuBtn->setObjectName("VectorButton_HW28_I20");
    m_pMenuBtn->setFont(iconFont);
    m_pMenuBtn->setText(QChar(0xe6e3));

    m_pUserInfoBtn = new VectorButton(this);
    m_pUserInfoBtn->setObjectName("VectorButton_HW28_I20");
    m_pUserInfoBtn->setFont(iconFont);
    m_pUserInfoBtn->setText(QChar(0xe66e));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(16, 0, 16, 0);
    layout->setSpacing(0);

    layout->addStretch();

    layout->addWidget(m_pBuyMemberBtn, 0, Qt::AlignVCenter);
    layout->addSpacing(4);
    layout->addWidget(m_pUserInfoBtn, 0, Qt::AlignVCenter);
    layout->addSpacing(4);
    layout->addWidget(m_pMenuBtn, 0, Qt::AlignVCenter);
    layout->addSpacing(8);
    layout->addWidget(createDividingLine(), 0, Qt::AlignVCenter);
    layout->addSpacing(8);
    layout->addWidget(m_pMinimizeBtn, 0, Qt::AlignVCenter);
    layout->addSpacing(4);
    layout->addWidget(m_pMaximizeBtn, 0, Qt::AlignVCenter);
    layout->addSpacing(4);
    layout->addWidget(m_pCloseBtn, 0, Qt::AlignVCenter);

    m_pLang = new LanguageFilter(this);
    auto movefilter = new MoveTitleBar(this, this->parentWidget());
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
}

void TitlebarView::slotMaximizeBtnClicked() {
}

void TitlebarView::slotMinimizeBtnClicked() {
}

void TitlebarView::slotMenuBtnClicked() {
}

void TitlebarView::slotUserInfoBtnClicked() {
}

void TitlebarView::slotBuyMemberBtnClicked() {
}