#pragma once
#include "globalpresenter.h"
#include "model.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class ConversionRepository : public Repository {
public:
    explicit ConversionRepository();
    ~ConversionRepository();
    QList<Data> datas();
    void appendData(QList<Data> datas);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

private:
    QList<Data> m_datas;
};