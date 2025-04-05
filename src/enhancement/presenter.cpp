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

QString EnhancementPresenter::getSampleImage1Path() {
    EnhancementRepository *rep = dynamic_cast<EnhancementRepository *>(repository());
    return rep->getSampleImage1Path();
}

QString EnhancementPresenter::getSampleImage2Path() {
    EnhancementRepository *rep = dynamic_cast<EnhancementRepository *>(repository());
    return rep->getSampleImage2Path();
}