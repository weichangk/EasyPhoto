#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "types.h"

using namespace QtmMvp;

class ImportListPresenter : public Presenter {
public:
    explicit ImportListPresenter(IView* view, IRepository *repository);
    ~ImportListPresenter();

    QList<SImageData> getDatas();
    void appendData(const QStringList filePaths);
    void deleteData(const QStringList filePaths);
    void clearData();
    int getDataIndex(const QString filePath);

private:
    QSet<QString> filePathsSet;
};