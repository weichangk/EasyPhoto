#pragma once
#include "globalpresenter.h"
#include "types.h"
#include "mvp/repository.h"

using namespace QtmMvp;

class ConversionRepository : public Repository {
public:
    explicit ConversionRepository();
    ~ConversionRepository();
    QList<SImageData> datas();
    void updateData(const SImageData &data);
    void updateData(const QString filePath, const SImageData &data);
    void appendData(QList<SImageData> datas);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

private:
    QList<SImageData> m_datas;
};