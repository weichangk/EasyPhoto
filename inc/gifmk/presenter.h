#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "types.h"
#include "observer/ifuncchangesubject.h"
#include "core/subject.h"

using namespace QtmMvp;
using namespace QtmCore;

class GifMkPresenter : public Presenter, public IFuncChangeSubject {
public:
    explicit GifMkPresenter(IView *view, IRepository *repository);
    ~GifMkPresenter();
    QList<SGifMkData> datas();
    void appendData(const QStringList filePaths);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();

    void funcChangeSubjectAttach(IFuncChangeObserver *observer) override;
    void funcChangeSubjectDetach(IFuncChangeObserver *observer) override;

private:
    bool handleMessage(IMessage* message) override;
    void funcChangeSubjectNotify(EFunc) override;

private:
    QSet<QString> filePathsSet;
    Subject<IFuncChangeObserver> m_pFuncChangeObserver;
};