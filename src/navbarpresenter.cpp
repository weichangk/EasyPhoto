#include "navbarpresenter.h"
#include "funcchangemessage.h"
#include "navbarcheckedmessage.h"

NavbarPresenter::NavbarPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

NavbarPresenter::~NavbarPresenter() {
}

void NavbarPresenter::funcChangeSubjectAttach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.attach(observer);
}

void NavbarPresenter::funcChangeSubjectDetach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.detach(observer);
}

void NavbarPresenter::funcChangeSubjectNotify(EFunc func) {
    m_pFuncChangeObserver.notify(&IFuncChangeObserver::funcChangeHandle, func);
}

void NavbarPresenter::navbarCheckedHandle(EFunc func) {
    NavbarCheckedMessage msg(func);
    view()->sendMessage(&msg);
}

bool NavbarPresenter::handleMessage(IMessage *message) {
    if (FuncChangeMessage *msg = dynamic_cast<FuncChangeMessage *>(message)) {
        funcChangeSubjectNotify((EFunc)msg->code());
    }
    return false;
}
