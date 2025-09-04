#pragma once
#include "globalpresenter.h"
#include "types.h"
#include "mvp/repository.h"

using namespace QtmMvp;

class BgRmRepository : public Repository {
public:
    explicit BgRmRepository();
    ~BgRmRepository();
    QList<SBgRmData> datas();
    void appendData(QList<SBgRmData> datas);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

private:
    QList<SBgRmData> m_datas;
};