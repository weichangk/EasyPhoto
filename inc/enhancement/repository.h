#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "model.h"

using namespace qtmaterialmvp;

class EnhancementRepository : public Repository {
public:
    explicit EnhancementRepository();
    ~EnhancementRepository();

    QList<SEnhanceModelData> getModelDatas();

    QString getSampleImage1Path();
    QString getSampleImage2Path();
};