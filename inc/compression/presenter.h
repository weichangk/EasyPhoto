#pragma once
#include "globalpresenter.h"
#include "model.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class CompressionPresenter : public Presenter {
public:
    explicit CompressionPresenter(IView *view, IRepository *repository);
    ~CompressionPresenter();
    QList<SCompressionData> datas();
    void appendData(const QStringList filePaths);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

private:
    QSet<QString> filePathsSet;
};