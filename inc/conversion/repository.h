#pragma once
#include "globalpresenter.h"
#include "model.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class ConversionRepository : public Repository {
public:
    explicit ConversionRepository();
    ~ConversionRepository();
    QList<SConversionData> datas();
    void appendData(QList<SConversionData> datas);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

private:
    QList<SConversionData> m_datas;
};