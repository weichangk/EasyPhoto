#include "bgrm/presenter.h"
#include "bgrm/repository.h"
#include "bgrm/view.h"

BgRmPresenter::BgRmPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
    BgRmView *bgRmView = dynamic_cast<BgRmView *>(view);
    BgRmRepository *bgRmRepository = dynamic_cast<BgRmRepository *>(repository);
    m_pImportListPresenter = new ImportListPresenter(bgRmView->getImportListView(), bgRmRepository->getImportListRepository());
}

BgRmPresenter::~BgRmPresenter() {
}

QString BgRmPresenter::getSampleImage1Path() {
    BgRmRepository *rep = dynamic_cast<BgRmRepository *>(repository());
    return rep->getSampleImage1Path();
}

QString BgRmPresenter::getSampleImage2Path() {
    BgRmRepository *rep = dynamic_cast<BgRmRepository *>(repository());
    return rep->getSampleImage2Path();
}