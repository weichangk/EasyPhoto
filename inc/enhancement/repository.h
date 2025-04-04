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
    // QList<SEnhanceInputData> getInputDatas();
    // void appendInputData(QList<SEnhanceInputData> datas);
    // void deleteInputData(const QStringList filePaths);
    // void clearInputData();
private:
    // QList<SEnhanceInputData> m_pInputDatas;
};