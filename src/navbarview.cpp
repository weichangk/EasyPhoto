#include "navbarview.h"
#include "funcenum.h"
#include "filter/movetitlebar.h"
#include "core/font.h"

using namespace qtmaterialfilter;
using namespace qtmaterialcore;

struct SNavIconName {
    QChar icon;
    QString name;
};

NavbarView::NavbarView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void NavbarView::setNavBtnChecked(EFunc func) {
    m_pNavBtnGroup->button(func)->setChecked(true);
}

void NavbarView::createUi() {
    setObjectName("NavbarView");
    setAttribute(Qt::WA_StyledBackground);
    setFixedWidth(200);

    QFont iconFont = Font::getIconFont(":/font/iconfont.ttf");

    m_pProjectLogo = new HorIconTextVectorButton(this);
    m_pProjectLogo->setObjectName("ProjectLogo");
    m_pProjectLogo->setFixedHeight(70);
    m_pProjectLogo->setIconTextSpacing(10);
    m_pProjectLogo->setIconSize(32);
    m_pProjectLogo->setIconFont(iconFont);
    m_pProjectLogo->setIcon(QChar(0xe601));
    m_pProjectLogo->setText("图片处理工具");

    auto navlayout = createNavBtns();

    auto layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_pProjectLogo, 0, Qt::AlignCenter);
    layout->addLayout(navlayout);
    layout->addStretch();

    auto movefilter = new MoveTitleBar(this, this->parentWidget());
}

void NavbarView::connectSig() {
}

QVBoxLayout *NavbarView::createNavBtns() {
    auto navlayout = new QVBoxLayout();
    navlayout->setAlignment(Qt::AlignCenter);
    navlayout->setContentsMargins(23, 20, 23, 13);
    navlayout->setSpacing(0);
    QMap<int, SNavIconName> navMap;
    navMap[EFunc::FuncConversion] = {QChar(0xe7dc), "图片转换"}; 
    navMap[EFunc::FuncCompression] = {QChar(0xe66b), "图片压缩"};
    navMap[EFunc::FuncCropping] = {QChar(0xe600), "图片裁剪"};
    navMap[EFunc::FuncErase] = {QChar(0xe789), "图片擦除"};
    navMap[EFunc::FuncEnhancement] = {QChar(0xe6a7), "图片增强"};
    navMap[EFunc::FuncInpainting] = {QChar(0xe771), "图片修复"};
    navMap[EFunc::FuncEffects] = {QChar(0xe677), "图片效果"};
    navMap[EFunc::FuncGifGeneration] = {QChar(0xe608), "GIF生成"};
    QMap<int, SNavIconName>::Iterator iter;
    QFont iconFont = Font::getIconFont(":/font/iconfont.ttf");
    m_pNavBtnGroup = new QButtonGroup(this);
    m_pNavBtnGroup->setExclusive(true);
    for (iter = navMap.begin(); iter != navMap.end(); ++iter) {
        auto *btn = new HorIconTextVectorButton(this);
        btn->setObjectName("HorIconTextVectorButton_H36_R8_I20_T14_Bg")
            ->setIconFont(iconFont)
            ->setIcon(iter.value().icon)
            ->setText(iter.value().name);
        btn->setFixedWidth(158);
        btn->setAdjustWidth(false);
        btn->setCheckable(true);
        m_pNavBtnGroup->addButton(btn, iter.key());
        navlayout->addWidget(btn);
        navlayout->addSpacing(4);
    }
    connect(m_pNavBtnGroup, &QButtonGroup::idClicked, this, [this](int id) {
        emit sigNavBtnClicked(id);
    });
    return navlayout;
}