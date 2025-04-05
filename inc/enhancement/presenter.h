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

    QString getSampleImage1Path();
    QString getSampleImage2Path();
};