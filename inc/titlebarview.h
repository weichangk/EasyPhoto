#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "widget/button.h"

using namespace qtmaterialmvp;
using namespace qtmaterialwidget;
using namespace qtmaterialcore;
using namespace qtmaterialfilter;

class TitlebarView : public QWidget, public View {
    Q_OBJECT
public:
    explicit TitlebarView(QWidget *parent = nullptr);
    ~TitlebarView() override {
    }

private:
    void createUi();
    void connectSig();
    QWidget *createDividingLine();

private slots:
    void slotLanguageChanged();
    void slotCloseBtnClicked();
    void slotMaximizeBtnClicked();
    void slotMinimizeBtnClicked();
    void slotMenuBtnClicked();
    void slotSupportBtnClicked();
    void slotUserInfoBtnClicked();
    void slotBuyMemberBtnClicked();

private:
    IconButton *m_pCloseBtn = nullptr;
    IconButton *m_pMaximizeBtn = nullptr;
    IconButton *m_pMinimizeBtn = nullptr;
    IconButton *m_pMenuBtn = nullptr;
    IconButton *m_pSupportBtn = nullptr;
    IconButton *m_pUserInfoBtn = nullptr;
    HorIconTextVectorButton *m_pBuyMemberBtn = nullptr;

    LanguageFilter *m_pLang = nullptr;
};