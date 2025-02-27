#include "home/presenter.h"
#include "home/repository.h"
#include "funcchangemessage.h"
#include "navbarcheckedmessage.h"

HomePresenter::HomePresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

HomePresenter::~HomePresenter() {
}

QList<SFuncItemData> HomePresenter::datas() {
    HomeRepository *rep = dynamic_cast<HomeRepository *>(repository());
    return rep->datas();
}

void HomePresenter::attach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.attach(observer);
}

void HomePresenter::detach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.detach(observer);
}

void HomePresenter::navbarCheckedSubjectAttach(INavbarCheckedObserver *observer) {
    m_pNavbarCheckedObserver.attach(observer);
}

void HomePresenter::navbarCheckedSubjectDetach(INavbarCheckedObserver *observer) {
    m_pNavbarCheckedObserver.detach(observer);
}

void HomePresenter::notifyFuncChange(EFunc func) {
    m_pFuncChangeObserver.notify(&IFuncChangeObserver::funcChange, func);
}

void HomePresenter::navbarCheckedNotify(EFunc func) {
    m_pNavbarCheckedObserver.notify(&INavbarCheckedObserver::navbarChecked, func);
}

bool HomePresenter::handleMessage(IMessage *message) {
    if (FuncChangeMessage *msg = dynamic_cast<FuncChangeMessage *>(message)) {
        notifyFuncChange((EFunc)msg->code());
    }
    if(NavbarCheckedMessage *msg = dynamic_cast<NavbarCheckedMessage *>(message)) {
        navbarCheckedNotify((EFunc)msg->code());
    }
    return false;
}
