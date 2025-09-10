#pragma once
#include "globalpresenter.h"
#include "types.h"
#include "mvp/repository.h"

using namespace QtmMvp;

class CompressionRepository : public Repository {
public:
    explicit CompressionRepository();
    ~CompressionRepository();
    QList<SCompressionData> datas();
    void updateData(const SCompressionData &data);
    void updateData(const QString filePath, const SCompressionData &data);
    void appendData(QList<SCompressionData> datas);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

private:
    QList<SCompressionData> m_datas;
};