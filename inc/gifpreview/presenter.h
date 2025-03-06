#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "observer/ifuncchangesubject.h"
#include "core/subject.h"

using namespace qtmaterialmvp;
using namespace qtmaterialcore;

class GifPreviewPresenter : public Presenter, public IFuncChangeSubject {
public:
    explicit GifPreviewPresenter(IView *view, IRepository *repository);
    ~GifPreviewPresenter();

    void funcChangeSubjectAttach(IFuncChangeObserver *observer) override;
    void funcChangeSubjectDetach(IFuncChangeObserver *observer) override;

private:
    bool handleMessage(IMessage* message) override;
    void funcChangeSubjectNotify(EFunc) override;

private:
    Subject<IFuncChangeObserver> m_pFuncChangeObserver;
};