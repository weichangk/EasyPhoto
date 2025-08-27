#pragma once
#include "globalpresenter.h"
#include "model.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace QtmMvp;

class BackgroungRemoverPresenter : public Presenter {
public:
    explicit BackgroungRemoverPresenter(IView* view, IRepository *repository);
    ~BackgroungRemoverPresenter();
    QList<SBGRemoverData> datas();
    void appendData(const QStringList filePaths);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

private:
    QSet<QString> filePathsSet;
};