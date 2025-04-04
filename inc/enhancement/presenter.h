#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "model.h"

using namespace qtmaterialmvp;

class EnhancementPresenter : public Presenter {
public:
    explicit EnhancementPresenter(IView* view, IRepository *repository);
    ~EnhancementPresenter();

    QList<SEnhanceModelData> getModelDatas();
    // QList<SEnhanceInputData> getInputDatas();
    // void appendInputData(QList<SEnhanceInputData> datas);
    // void deleteInputData(const QStringList filePaths);
    // void clearInputData();
};