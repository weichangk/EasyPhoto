#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "importmodel.h"

using namespace qtmaterialmvp;

class ImportListRepository : public Repository {
public:
    explicit ImportListRepository();
    ~ImportListRepository();

    QList<SImportListItem> getDatas();
    void appendData(QList<SImportListItem> datas);
    void deleteData(const QStringList filePaths);
    void clearData();
private:
    QList<SImportListItem> m_pDatas;
};