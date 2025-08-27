#pragma once
#include "globalview.h"
#include "funcenum.h"
#include "mvp/view.h"
#include "widget/button.h"
#include "freetrialtimerview.h"

#include <QButtonGroup>

using namespace QtmMvp;
using namespace QtmWidget;
using namespace QtmFilter;

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
    void clearNavBtnChecked();

private:
    bool handleMessage(IMessage *message) override;

private slots:
    void onLanguageChange();
    void onNavBtnClicked(int);

private:
    LanguageFilter *m_pLang = nullptr;

    HorIconTextButton *m_pProjectLogo = nullptr;
    HorIconTextButton *m_pHomeBtn = nullptr;
    HorIconTextButton *m_pMyFileBtn = nullptr;
    HorIconTextButton *m_pConversionBtn = nullptr;
    HorIconTextButton *m_pCompressionBtn = nullptr;
    HorIconTextButton *m_pCroppingBtn = nullptr;
    HorIconTextButton *m_pEraseBtn = nullptr;
    HorIconTextButton *m_pEnhancementBtn = nullptr;
    HorIconTextButton *m_pInpaintingBtn = nullptr;
    HorIconTextButton *m_pEffectsBtn = nullptr;
    HorIconTextButton *m_pGifgenerationBtn = nullptr;
    QButtonGroup *m_pNavBtnGroup = nullptr;

    FreeTrialTimerView *m_FreeTrialTimerView = nullptr;
};