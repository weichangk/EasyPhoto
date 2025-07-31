#pragma once
#include "globalpresenter.h"
#include "model.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "task/asynctask.h"
#include "task/taskresult.h"
#include "import/importfilehelper.h"

using namespace qtmaterialmvp;
using namespace qtmaterialtask;

class CompressionPresenter : public Presenter {
public:
    explicit CompressionPresenter(IView *view, IRepository *repository);
    ~CompressionPresenter();
    QList<SCompressionData> datas();
    void updateData(const SCompressionData &data);
    void updateData(const QString filePath, const SCompressionData &data);
    void appendData(const QStringList filePaths);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

    TaskResult<SImportFileResult<QList<SCompressionData>>> importFileAsync(AsyncTask<SImportFileData, SImportFileResult<QList<SCompressionData>>> *self);
    void appendData(const QList<SCompressionData> datas);

private:
    QSet<QString> filePathsSet;
};