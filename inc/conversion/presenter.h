#pragma once
#include "globalpresenter.h"
#include "model.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class ConversionPresenter : public Presenter {
public:
    explicit ConversionPresenter(IView* view, IRepository *repository);
    ~ConversionPresenter();
    QList<SConversionData> datas();
    void appendData(const QStringList filePaths);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();
    void switchCheckedData(const QString filePath);
    void checkedAllData(bool checked);

private:
    QSet<QString> filePathsSet;
};