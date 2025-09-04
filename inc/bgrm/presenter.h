#pragma once
#include "globalpresenter.h"
#include "types.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace QtmMvp;

class BgRmPresenter : public Presenter {
public:
    explicit BgRmPresenter(IView* view, IRepository *repository);
    ~BgRmPresenter();
    QList<SBgRmData> datas();
    void appendData(const QStringList filePaths);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

private:
    QSet<QString> filePathsSet;
};