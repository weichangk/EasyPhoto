#pragma once
#include "globalpresenter.h"
#include "model.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class BackgroungRemoverRepository : public Repository {
public:
    explicit BackgroungRemoverRepository();
    ~BackgroungRemoverRepository();
    QList<SBGRemoverData> datas();
    void appendData(QList<SBGRemoverData> datas);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

private:
    QList<SBGRemoverData> m_datas;
};