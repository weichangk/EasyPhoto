#pragma once
#include "globalpresenter.h"
#include "titlebarpresenter.h"
#include "navbarpresenter.h"
#include "funcareapresenter.h"
#include "ititlebarfuncobserver.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class MainPresenter : public Presenter, public ITitlebarFuncObserver {
public:
    explicit MainPresenter(IView* view, IRepository *repository);
    ~MainPresenter();

    void titleBarFuncHandle(ETitleBarFunc) override;
    
private:
    TitlebarPresenter *m_pTitlebarPresenter = nullptr;
    NavbarPresenter *m_pNavbarPresenter = nullptr;
    FuncAreaPresenter *m_pFuncAreaPresenter = nullptr;
};