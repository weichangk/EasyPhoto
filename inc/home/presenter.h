#pragma once
#include "globalpresenter.h"
#include "model.h"
#include "ifuncchangesubject.h"
#include "inavbarcheckedsubject.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "core/subject.h"

using namespace qtmaterialmvp;
using namespace qtmaterialcore;

class HomePresenter : public Presenter, public IFuncChangeSubject, public INavbarCheckedSubject {
public:
    explicit HomePresenter(IView* view, IRepository *repository);
    ~HomePresenter();

    QList<SFuncItemData> datas();

    void attach(IFuncChangeObserver *observer) override;
    void detach(IFuncChangeObserver *observer) override;

    void navbarCheckedSubjectAttach(INavbarCheckedObserver *observer) override;
    void navbarCheckedSubjectDetach(INavbarCheckedObserver *observer) override;

private:
    void notifyFuncChange(EFunc) override;
    void navbarCheckedNotify(EFunc) override;

    bool handleMessage(IMessage* message) override;

private:
    Subject<IFuncChangeObserver> m_pFuncChangeObserver;
    Subject<INavbarCheckedObserver> m_pNavbarCheckedObserver;
};