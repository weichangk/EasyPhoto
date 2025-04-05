#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "importmodel.h"

using namespace qtmaterialmvp;

class ImportListPresenter : public Presenter {
public:
    explicit ImportListPresenter(IView* view, IRepository *repository);
    ~ImportListPresenter();

    QList<SImportListItem> getDatas();
    void appendData(const QStringList filePaths);
    void deleteData(const QStringList filePaths);
    void clearData();
};