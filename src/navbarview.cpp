#include "navbarview.h"
#include "message/funcchangemessage.h"
#include "message/navbarcheckedmessage.h"
#include "funcenum.h"
#include "filter/movetitlebar.h"
#include "core/font.h"
#include "core/theme.h"

using namespace QtmFilter;
using namespace QtmCore;

struct SNavIconName {
    QString icon;
    QString name;
};

NavbarView::NavbarView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

void NavbarView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    #ifdef IS_MVP
        onNavBtnClicked(EFunc::FuncUpsc);
        m_pNavBtnGroup->button(EFunc::FuncUpsc)->setChecked(true);
    #endif
}

void NavbarView::createUi() {
    setObjectName("NavbarView");
    setAttribute(Qt::WA_StyledBackground);
    setFixedWidth(200);

    m_pProjectLogo = new HorIconTextButton(this);
    m_pProjectLogo->setObjectName("NavbarView_m_pProjectLogo");
    m_pProjectLogo->setFixedHeight(70);
    m_pProjectLogo->setIconTextSpacing(4);
    m_pProjectLogo->setIconSize(40, 40);
    m_pProjectLogo->setNormalPixmapPath(":/logo");

    #ifdef IS_MVP
        auto navlayout = createNavBtnsMVP();
    #else
        auto navlayout = createNavBtns();
    #endif

    m_FreeTrialTimerView = new FreeTrialTimerView(this);

    auto layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 16, 0, 20);
    layout->setSpacing(0);
    layout->addWidget(m_pProjectLogo, 0, Qt::AlignCenter);
    layout->addLayout(navlayout);
    layout->addStretch();
    layout->addWidget(m_FreeTrialTimerView, 0, Qt::AlignCenter);

    m_pLang = new LanguageFilter(this);
    auto movefilter = new MoveTitleBar(this, this->parentWidget());
}

void NavbarView::connectSig() {
    bool bIsConn = false;
    bIsConn = connect(m_pLang, &LanguageFilter::sigLanguageChange, this, &NavbarView::onLanguageChange);
    Q_ASSERT(bIsConn);
}

QVBoxLayout *NavbarView::createNavBtnsMVP() {
    auto navlayout = new QVBoxLayout();
    navlayout->setAlignment(Qt::AlignCenter);
    navlayout->setContentsMargins(23, 20, 23, 13);
    navlayout->setSpacing(0);
    QMap<int, SNavIconName> navMap;
    navMap[EFunc::FuncUpsc] = {QString(":/QtmImg/img/%1/v16/icon24/icon24_photo enhancer.svg").arg(QtmCore::Theme::currentTheme()), tr("Image Enhancer")}; 
    navMap[EFunc::FuncBgRm] = {QString(":/QtmImg/img/%1/v16/icon24/icon24_background remover.svg").arg(QtmCore::Theme::currentTheme()), tr("Image BG Remover")}; 
    navMap[EFunc::FuncGifMk] = {QString(":/QtmImg/img/%1/v16/icon24/icon24_gif maker.svg").arg(QtmCore::Theme::currentTheme()), tr("GIF Maker")}; 
    navMap[EFunc::FuncConversion] = {QString(":/QtmImg/img/%1/v16/icon24/icon24_converter.svg").arg(QtmCore::Theme::currentTheme()), tr("Converter")}; 
    navMap[EFunc::FuncCompression] = {QString(":/QtmImg/img/%1/v16/icon24/icon24_compress.svg").arg(QtmCore::Theme::currentTheme()), tr("Compressor")}; 
    QMap<int, SNavIconName>::Iterator iter;
    m_pNavBtnGroup = new QButtonGroup(this);
    m_pNavBtnGroup->setExclusive(true);
    for (iter = navMap.begin(); iter != navMap.end(); ++iter) {
        auto *btn = new HorIconTextButton(this, style::EHorIconTexAligns::Left);
        btn->setObjectName("NavbarView_m_pNavbarBtn");
        btn->setNormalPixmapPath(iter.value().icon);
        btn->setText(iter.value().name);
        btn->setIconSize(24, 24);
        btn->setFixedSize(158, 40);
        btn->setAdjustWidth(false);
        btn->setCheckable(true);
        m_pNavBtnGroup->addButton(btn, iter.key());
        navlayout->addWidget(btn);
        navlayout->addSpacing(8);
    }
    connect(m_pNavBtnGroup, &QButtonGroup::idClicked, this, &NavbarView::onNavBtnClicked);
    return navlayout;
}

QVBoxLayout *NavbarView::createNavBtns() {
    auto navlayout = new QVBoxLayout();
    navlayout->setAlignment(Qt::AlignCenter);
    navlayout->setContentsMargins(23, 20, 23, 13);
    navlayout->setSpacing(0);
    QMap<int, SNavIconName> navMap;
    navMap[EFunc::FuncHome] = {QString(":/QtmImg/img/%1/v16/icon24/icon24_home.svg").arg(QtmCore::Theme::currentTheme()), tr("Home")}; 
    navMap[EFunc::FuncMyFile] = {QString(":/QtmImg/img/%1/v16/icon24/icon24_file.svg").arg(QtmCore::Theme::currentTheme()), tr("My Files")}; 
    navMap[EFunc::FuncConversion] = {QString(":/QtmImg/img/%1/v16/icon24/icon24_converter.svg").arg(QtmCore::Theme::currentTheme()), tr("Converter")}; 
    navMap[EFunc::FuncCompression] = {QString(":/QtmImg/img/%1/v16/icon24/icon24_compress.svg").arg(QtmCore::Theme::currentTheme()), tr("Compressor")}; 
    // navMap[EFunc::FuncCropping] = {"", "图片裁剪"};
    // navMap[EFunc::FuncErase] = {"", "图片擦除"};
    // navMap[EFunc::FuncEnhancement] = {"", "图片增强"};
    // navMap[EFunc::FuncInpainting] = {"", "图片修复"};
    // navMap[EFunc::FuncEffects] = {"", "图片效果"};
    navMap[EFunc::FuncGifMk] = {QString(":/QtmImg/img/%1/v16/icon24/icon24_gif maker.svg").arg(QtmCore::Theme::currentTheme()), tr("GIF Maker")}; 
    QMap<int, SNavIconName>::Iterator iter;
    m_pNavBtnGroup = new QButtonGroup(this);
    m_pNavBtnGroup->setExclusive(true);
    for (iter = navMap.begin(); iter != navMap.end(); ++iter) {
        auto *btn = new HorIconTextButton(this, style::EHorIconTexAligns::Left);
        btn->setObjectName("NavbarView_m_pNavbarBtn");
        btn->setNormalPixmapPath(iter.value().icon);
        btn->setText(iter.value().name);
        btn->setIconSize(24, 24);
        btn->setFixedSize(158, 40);
        btn->setAdjustWidth(false);
        btn->setCheckable(true);
        m_pNavBtnGroup->addButton(btn, iter.key());
        navlayout->addWidget(btn);
        if(iter.key() == EFunc::FuncMyFile) {
            navlayout->addSpacing(20);
            auto *hot = new HorIconTextButton(this, style::EHorIconTexAligns::Left);
            hot->setObjectName("NavbarView_m_pNavbarHot");
            hot->setNormalPixmapPath(QString(":/QtmImg/img/%1/v16/icon20/icon20_hot.png").arg(QtmCore::Theme::currentTheme()));
            hot->setText(tr("Hot"));
            hot->setIconSize(20, 20);
            hot->setFixedSize(158, 40);
            navlayout->addWidget(hot);
        }
        else {
            navlayout->addSpacing(8);
        }
    }
    connect(m_pNavBtnGroup, &QButtonGroup::idClicked, this, &NavbarView::onNavBtnClicked);
    return navlayout;
}

void NavbarView::setNavBtnChecked(EFunc func) {
    auto btn = m_pNavBtnGroup->button(func);
    if (btn) {
        btn->setChecked(true);
    } 
}

void NavbarView::clearNavBtnChecked() {
    m_pNavBtnGroup->setExclusive(false);
    for (auto btn : m_pNavBtnGroup->buttons()) {
        btn->setChecked(false);
    }
    m_pNavBtnGroup->setExclusive(true);
}

bool NavbarView::handleMessage(IMessage *message) {
    if (NavbarCheckedMessage *msg = dynamic_cast<NavbarCheckedMessage *>(message)) {
        clearNavBtnChecked();
        setNavBtnChecked((EFunc)msg->code());
    }
    return false;
}

void NavbarView::onLanguageChange() {
    m_pProjectLogo->setText(tr("EasyPhoto"));
}

void NavbarView::onNavBtnClicked(int func) {
    FuncChangeMessage msg(func);
    presenter()->sendMessage(&msg);
}