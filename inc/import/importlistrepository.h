#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "types.h"

using namespace QtmMvp;

class ImportListRepository : public Repository {
public:
    explicit ImportListRepository();
    ~ImportListRepository();

    QList<SImageData> getDatas();
    void appendData(QList<SImageData> datas);
    void deleteData(const QStringList filePaths);
    void clearData();
    int getDataIndex(const QString filePath);
private:
    QList<SImageData> m_pDatas;
};