#pragma once
#include "globalpresenter.h"
#include "navbarsubject.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "core/subject.h"

using namespace qtmaterialmvp;

class NavbarPresenter : public Presenter, public INavbarSubject {
public:
    explicit NavbarPresenter(IView* view, IRepository *repository);
    ~NavbarPresenter();

    void attach(INavbarObserver *observer) override;
    void detach(INavbarObserver *observer) override;

private:
    void notifyNavChange(EFunc) override;
    bool handleMessage(IMessage* message) override;

private:
    qtmaterialcore::Subject<INavbarObserver> m_pNavbarObserver;
};