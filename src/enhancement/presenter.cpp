#include "enhancement/presenter.h"
#include "enhancement/repository.h"

EnhancementPresenter::EnhancementPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

EnhancementPresenter::~EnhancementPresenter() {
}

QList<SEnhanceModelData> EnhancementPresenter::getModelDatas() {
    EnhancementRepository *rep = dynamic_cast<EnhancementRepository *>(repository());
    return rep->getModelDatas();
}

// QList<SEnhanceInputData> EnhancementPresenter::getInputDatas() {
//     EnhancementRepository *rep = dynamic_cast<EnhancementRepository *>(repository());
//     return rep->getInputDatas();
// }

// void EnhancementPresenter::appendInputData(QList<SEnhanceInputData> datas) {
//     EnhancementRepository *rep = dynamic_cast<EnhancementRepository *>(repository());
//     rep->appendInputData(datas);
// }

// void EnhancementPresenter::deleteInputData(const QStringList filePaths) {
//     EnhancementRepository *rep = dynamic_cast<EnhancementRepository *>(repository());
//     rep->deleteInputData(filePaths);
// }

// void EnhancementPresenter::clearInputData() {
//     EnhancementRepository *rep = dynamic_cast<EnhancementRepository *>(repository());
//     rep->clearInputData();
// }