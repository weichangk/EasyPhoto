#pragma once
#include "globalpresenter.h"
#include "ifuncchangesubject.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "core/subject.h"

using namespace qtmaterialmvp;

class NavbarPresenter : public Presenter, public IFuncChangeSubject {
public:
    explicit NavbarPresenter(IView* view, IRepository *repository);
    ~NavbarPresenter();

    void attach(IFuncChangeObserver *observer) override;
    void detach(IFuncChangeObserver *observer) override;

private:
    void notifyFuncChange(EFunc) override;
    bool handleMessage(IMessage* message) override;

private:
    qtmaterialcore::Subject<IFuncChangeObserver> m_pFuncChangeObserver;
};