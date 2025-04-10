#include "cropping/presenter.h"
#include "cropping/repository.h"
#include "cropping/view.h"

CroppingPresenter::CroppingPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
    CroppingView *croppingView = dynamic_cast<CroppingView *>(view);
    CroppingRepository *eraseRepository = dynamic_cast<CroppingRepository *>(repository);
    m_pImportListPresenter = new ImportListPresenter(croppingView->getImportListView(), eraseRepository->getImportListRepository());
}

CroppingPresenter::~CroppingPresenter() {
}

QString CroppingPresenter::getSampleImage1Path() {
    CroppingRepository *rep = dynamic_cast<CroppingRepository *>(repository());
    return rep->getSampleImage1Path();
}

QString CroppingPresenter::getSampleImage2Path() {
    CroppingRepository *rep = dynamic_cast<CroppingRepository *>(repository());
    return rep->getSampleImage2Path();
}