#include "erase/presenter.h"
#include "erase/repository.h"
#include "erase/view.h"

ErasePresenter::ErasePresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
    EraseView *eraseView = dynamic_cast<EraseView *>(view);
    EraseRepository *eraseRepository = dynamic_cast<EraseRepository *>(repository);
    m_pImportListPresenter = new ImportListPresenter(eraseView->getImportListView(), eraseRepository->getImportListRepository());
}

ErasePresenter::~ErasePresenter() {
}

QString ErasePresenter::getSampleImage1Path() {
    EraseRepository *rep = dynamic_cast<EraseRepository *>(repository());
    return rep->getSampleImage1Path();
}

QString ErasePresenter::getSampleImage2Path() {
    EraseRepository *rep = dynamic_cast<EraseRepository *>(repository());
    return rep->getSampleImage2Path();
}