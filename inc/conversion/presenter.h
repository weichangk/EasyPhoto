#pragma once
#include "globalpresenter.h"
#include "types.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "task/asynctask.h"
#include "task/taskresult.h"
#include "import/importfilehelper.h"

using namespace QtmMvp;
using namespace QtmTask;

class ConversionPresenter : public Presenter {
public:
    explicit ConversionPresenter(IView* view, IRepository *repository);
    ~ConversionPresenter();
    QList<SImageData> datas();
    void updateData(const SImageData &data);
    void updateData(const QString filePath, const SImageData &data);
    void appendData(const QStringList filePaths);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

    TaskResult<SImportFileResult<QList<SImageData>>> importFileAsync(AsyncTask<SImportFileData, SImportFileResult<QList<SImageData>>> *self);
    void appendData(const QList<SImageData> datas);

private:
    QSet<QString> filePathsSet;
};