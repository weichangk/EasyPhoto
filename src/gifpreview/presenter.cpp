#include "gifpreview/presenter.h"
#include "gifpreview/repository.h"
#include "message/funcchangemessage.h"

GifPreviewPresenter::GifPreviewPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

GifPreviewPresenter::~GifPreviewPresenter() {
}

void GifPreviewPresenter::funcChangeSubjectAttach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.attach(observer);
}

void GifPreviewPresenter::funcChangeSubjectDetach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.detach(observer);
}

bool GifPreviewPresenter::handleMessage(IMessage *message) {
    if (FuncChangeMessage *msg = dynamic_cast<FuncChangeMessage *>(message)) {
        funcChangeSubjectNotify((EFunc)msg->code());
    }
    return false;
}

void GifPreviewPresenter::funcChangeSubjectNotify(EFunc func) {
    m_pFuncChangeObserver.notify(&IFuncChangeObserver::funcChangeHandle, func);
}