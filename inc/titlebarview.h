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
    void slotUserInfoBtnClicked();
    void slotBuyMemberBtnClicked();

private:
    VectorButton *m_pCloseBtn = nullptr;
    VectorButton *m_pMaximizeBtn = nullptr;
    VectorButton *m_pMinimizeBtn = nullptr;
    VectorButton *m_pMenuBtn = nullptr;
    VectorButton *m_pUserInfoBtn = nullptr;
    HorIconTextVectorButton *m_pBuyMemberBtn = nullptr;

    LanguageFilter *m_pLang = nullptr;
};