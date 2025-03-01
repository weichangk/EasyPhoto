#pragma once
#include "globalpresenter.h"
#include "ititlebarfuncsubject.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "core/subject.h"

using namespace qtmaterialmvp;
using namespace qtmaterialcore;

class TitlebarPresenter : public Presenter, public ITitlebarFuncSubject {
public:
    explicit TitlebarPresenter(IView *view, IRepository *repository);
    ~TitlebarPresenter();

    void titlebarFuncSubjectAttach(ITitlebarFuncObserver *observer) override;
    void titlebarFuncSubjectDetach(ITitlebarFuncObserver *observer) override;

private:
    void titlebarFuncSubjectNotify(ETitleBarFunc func) override;
    bool handleMessage(IMessage *message) override;

private:
    Subject<ITitlebarFuncObserver> m_pTitlebarFuncObserver;
};