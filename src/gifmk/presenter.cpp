#include "gifmk/presenter.h"
#include "gifmk/repository.h"
#include "gifmk/view.h"
#include "message/funcchangemessage.h"

#include <QFileInfo>

GifMkPresenter::GifMkPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
    GifMkView *gifMkView = dynamic_cast<GifMkView *>(view);
    GifMkRepository *gifMkRepository = dynamic_cast<GifMkRepository *>(repository);
    m_pImportListPresenter = new ImportListPresenter(gifMkView->getImportListView(), gifMkRepository->getImportListRepository());
}

GifMkPresenter::~GifMkPresenter() {
}

QList<SImageData> GifMkPresenter::getDatas() {
    return m_pImportListPresenter->getDatas();
}

void GifMkPresenter::funcChangeSubjectAttach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.attach(observer);
}

void GifMkPresenter::funcChangeSubjectDetach(IFuncChangeObserver *observer) {
    m_pFuncChangeObserver.detach(observer);
}

bool GifMkPresenter::handleMessage(IMessage *message) {
    if (FuncChangeMessage *msg = dynamic_cast<FuncChangeMessage *>(message)) {
        funcChangeSubjectNotify((EFunc)msg->code());
    }
    return false;
}

void GifMkPresenter::funcChangeSubjectNotify(EFunc func) {
    m_pFuncChangeObserver.notify(&IFuncChangeObserver::funcChangeHandle, func);
}