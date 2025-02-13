#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "model.h"

using namespace qtmaterialmvp;

class GifGenerationPresenter : public Presenter {
public:
    explicit GifGenerationPresenter(IView* view, IRepository *repository);
    ~GifGenerationPresenter();
    QList<SGifGenerationData> datas();
    void appendData(const QStringList filePaths);
    void deleteData(const QStringList filePaths);
    void deleteCheckedData();
    void clearData();

private:
    QSet<QString> filePathsSet;
};