#pragma once
#include "globalpresenter.h"
#include "ifuncchangesubject.h"
#include "inavbarcheckedobserver.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "core/subject.h"

using namespace qtmaterialmvp;

class NavbarPresenter : public Presenter, public IFuncChangeSubject, public INavbarCheckedObserver {
public:
    explicit NavbarPresenter(IView* view, IRepository *repository);
    ~NavbarPresenter();

    void funcChangeSubjectAttach(IFuncChangeObserver *observer) override;
    void funcChangeSubjectDetach(IFuncChangeObserver *observer) override;

private:
    void funcChangeSubjectNotify(EFunc) override;
    
    void navbarCheckedHandle(EFunc) override;

    bool handleMessage(IMessage* message) override;

private:
    qtmaterialcore::Subject<IFuncChangeObserver> m_pFuncChangeObserver;
};