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

class ConversionPresenter : public Presenter {
public:
    explicit ConversionPresenter(IView* view, IRepository *repository);
    ~ConversionPresenter();
    QList<SConversionData> datas();
    void updateData(const SConversionData &data);
    void updateData(const QString filePath, const SConversionData &data);
    void appendData(const QStringList filePaths);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

    TaskResult<SImportFileResult<QList<SConversionData>>> importFileAsync(AsyncTask<SImportFileData, SImportFileResult<QList<SConversionData>>> *self);
    void appendData(const QList<SConversionData> datas);

private:
    QSet<QString> filePathsSet;
};