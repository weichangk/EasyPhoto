#include "enhancement/presenter.h"
#include "enhancement/repository.h"
#include "enhancement/view.h"

EnhancementPresenter::EnhancementPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
    EnhancementView *enhancementView = dynamic_cast<EnhancementView *>(view);
    EnhancementRepository *enhancementRepository = dynamic_cast<EnhancementRepository *>(repository);
    m_pImportListPresenter = new ImportListPresenter(enhancementView->getImportListView(), enhancementRepository->getImportListRepository());
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