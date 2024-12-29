#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "titlebarview.h"
#include "navbarview.h"
#include "funcareaview.h"

using namespace qtmaterialmvp;

class MainView : public QWidget, public View {
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView() override {
    }

private:
    void createUi();
    void connectSig();

private:
    TitlebarView *m_pTitlebarView = nullptr;
    NavbarView *m_pNavbarView = nullptr;
    FuncAreaView *m_pFuncAreaView = nullptr;
};