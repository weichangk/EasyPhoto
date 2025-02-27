#include "navbarpresenter.h"
#include "funcchangemessage.h"
#include "navbarcheckedmessage.h"

NavbarPresenter::NavbarPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

NavbarPresenter::~NavbarPresenter() {
}

void NavbarPresenter::attach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.attach(observer);
}

void NavbarPresenter::detach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.detach(observer);
}

void NavbarPresenter::notifyFuncChange(EFunc func) {
    m_pFuncChangeObserver.notify(&IFuncChangeObserver::funcChange, func);
}

void NavbarPresenter::navbarChecked(EFunc func) {
    NavbarCheckedMessage msg(func);
    view()->sendMessage(&msg);
}

bool NavbarPresenter::handleMessage(IMessage *message) {
    if (FuncChangeMessage *msg = dynamic_cast<FuncChangeMessage *>(message)) {
        notifyFuncChange((EFunc)msg->code());
    }
    return false;
}
