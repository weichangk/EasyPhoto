#pragma once
#include "globalpresenter.h"
#include "model.h"
#include "observer/ifuncchangesubject.h"
#include "observer/inavbarcheckedsubject.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "core/subject.h"

using namespace QtmMvp;
using namespace QtmCore;

class HomePresenter : public Presenter, public IFuncChangeSubject, public INavbarCheckedSubject {
public:
    explicit HomePresenter(IView* view, IRepository *repository);
    ~HomePresenter();

    QList<SFuncItemData> datas();

    void funcChangeSubjectAttach(IFuncChangeObserver *observer) override;
    void funcChangeSubjectDetach(IFuncChangeObserver *observer) override;

    void navbarCheckedSubjectAttach(INavbarCheckedObserver *observer) override;
    void navbarCheckedSubjectDetach(INavbarCheckedObserver *observer) override;

private:
    void funcChangeSubjectNotify(EFunc) override;
    void navbarCheckedSubjectNotify(EFunc) override;

    bool handleMessage(IMessage* message) override;

private:
    Subject<IFuncChangeObserver> m_pFuncChangeObserver;
    Subject<INavbarCheckedObserver> m_pNavbarCheckedObserver;
};