#include "enhancement/repository.h"

EnhancementRepository::EnhancementRepository() {
}

EnhancementRepository::~EnhancementRepository() {
}

QList<SEnhanceModelData> EnhancementRepository::getModelDatas() {
    QList<SEnhanceModelData> datas;
    return datas;
}

QList<SEnhanceInputData> EnhancementRepository::getInputDatas() {
    return m_pInputDatas;
}

void EnhancementRepository::appendInputData(QList<SEnhanceInputData> datas) {
    m_pInputDatas.append(datas);
}

void EnhancementRepository::deleteInputData(const QStringList filePaths) {
    auto func = [](const SEnhanceInputData &cd, const QStringList &filePaths) {
        return filePaths.contains(cd.path);
    };
    m_pInputDatas.erase(std::remove_if(m_pInputDatas.begin(), m_pInputDatas.end(), std::bind(func, std::placeholders::_1, filePaths)), m_pInputDatas.end());
}

void EnhancementRepository::clearInputData() {
    m_pInputDatas.clear();
}