#pragma once
#include "globalview.h"
#include "funcenum.h"
#include "mvp/view.h"
#include "widget/button.h"

#include <QButtonGroup>

using namespace qtmaterialmvp;
using namespace qtmaterialwidget;
using namespace qtmaterialfilter;

class NavbarView : public QWidget, public View {
    Q_OBJECT
public:
    explicit NavbarView(QWidget *parent = nullptr);
    ~NavbarView() override {
    }

private:
    void createUi();
    void connectSig();
    QVBoxLayout *createNavBtns();
    void setNavBtnChecked(EFunc);

private slots:
    void onLanguageChange();
    void onNavBtnClicked(int);

private:
    LanguageFilter *m_pLang = nullptr;

    HorIconTextButton *m_pProjectLogo = nullptr;
    HorIconTextVectorButton *m_pConversionBtn = nullptr;
    HorIconTextVectorButton *m_pCompressionBtn = nullptr;
    HorIconTextVectorButton *m_pCroppingBtn = nullptr;
    HorIconTextVectorButton *m_pEraseBtn = nullptr;
    HorIconTextVectorButton *m_pEnhancementBtn = nullptr;
    HorIconTextVectorButton *m_pInpaintingBtn = nullptr;
    HorIconTextVectorButton *m_pEffectsBtn = nullptr;
    HorIconTextVectorButton *m_pGifgenerationBtn = nullptr;
    QButtonGroup *m_pNavBtnGroup = nullptr;
};