#include "crop/presenter.h"
#include "crop/repository.h"
#include "crop/view.h"

CropPresenter::CropPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
    CropView *croppingView = dynamic_cast<CropView *>(view);
    CropRepository *eraseRepository = dynamic_cast<CropRepository *>(repository);
    m_pImportListPresenter = new ImportListPresenter(croppingView->getImportListView(), eraseRepository->getImportListRepository());
}

CropPresenter::~CropPresenter() {
}

QString CropPresenter::getSampleImage1Path() {
    CropRepository *rep = dynamic_cast<CropRepository *>(repository());
    return rep->getSampleImage1Path();
}

QString CropPresenter::getSampleImage2Path() {
    CropRepository *rep = dynamic_cast<CropRepository *>(repository());
    return rep->getSampleImage2Path();
}