#pragma once
#include "globalpresenter.h"
#include "titlebarpresenter.h"
#include "navbarpresenter.h"
#include "funcareapresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class MainPresenter : public Presenter {
public:
    explicit MainPresenter(IView* view, IRepository *repository);
    ~MainPresenter();

private:
    TitlebarPresenter *m_pTitlebarPresenter = nullptr;
    NavbarPresenter *m_pNavbarPresenter = nullptr;
    FuncAreaPresenter *m_pFuncAreaPresenter = nullptr;
};