#include "home/presenter.h"
#include "home/repository.h"
#include "message/funcchangemessage.h"
#include "message/navbarcheckedmessage.h"

HomePresenter::HomePresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

HomePresenter::~HomePresenter() {
}

QList<SFuncItemData> HomePresenter::datas() {
    HomeRepository *rep = dynamic_cast<HomeRepository *>(repository());
    return rep->datas();
}

void HomePresenter::funcChangeSubjectAttach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.attach(observer);
}

void HomePresenter::funcChangeSubjectDetach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.detach(observer);
}

void HomePresenter::navbarCheckedSubjectAttach(INavbarCheckedObserver *observer) {
    m_pNavbarCheckedObserver.attach(observer);
}

void HomePresenter::navbarCheckedSubjectDetach(INavbarCheckedObserver *observer) {
    m_pNavbarCheckedObserver.detach(observer);
}

void HomePresenter::funcChangeSubjectNotify(EFunc func) {
    m_pFuncChangeObserver.notify(&IFuncChangeObserver::funcChangeHandle, func);
}

void HomePresenter::navbarCheckedSubjectNotify(EFunc func) {
    m_pNavbarCheckedObserver.notify(&INavbarCheckedObserver::navbarCheckedHandle, func);
}

bool HomePresenter::handleMessage(IMessage *message) {
    if (FuncChangeMessage *msg = dynamic_cast<FuncChangeMessage *>(message)) {
        funcChangeSubjectNotify((EFunc)msg->code());
    }
    if(NavbarCheckedMessage *msg = dynamic_cast<NavbarCheckedMessage *>(message)) {
        navbarCheckedSubjectNotify((EFunc)msg->code());
    }
    return false;
}
