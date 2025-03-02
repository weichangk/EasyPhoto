#include "titlebarpresenter.h"
#include "message/titlebarfuncmessage.h"
#include "titlebarenum.h"

TitlebarPresenter::TitlebarPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

TitlebarPresenter::~TitlebarPresenter() {
}

void TitlebarPresenter::titlebarFuncSubjectAttach(ITitlebarFuncObserver *observer) {
    m_pTitlebarFuncObserver.attach(observer);
}

void TitlebarPresenter::titlebarFuncSubjectDetach(ITitlebarFuncObserver *observer) {
    m_pTitlebarFuncObserver.detach(observer);
}

void TitlebarPresenter::titlebarFuncSubjectNotify(ETitleBarFunc func) {
    m_pTitlebarFuncObserver.notify(&ITitlebarFuncObserver::titleBarFuncHandle, func);
}

bool TitlebarPresenter::handleMessage(IMessage *message) {
    if (TitlebarFuncMessage *msg = dynamic_cast<TitlebarFuncMessage *>(message)) {
        titlebarFuncSubjectNotify((ETitleBarFunc)msg->code());
    }
    return false;
}