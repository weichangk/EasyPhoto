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
    QList<Data> datas();
    void appendData(const QStringList filePaths);

private:
    QSet<QString> filePathsSet;
};