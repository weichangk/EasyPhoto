#include "thumbmaker/presenter.h"

ThumbnailMakerPresenter::ThumbnailMakerPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

ThumbnailMakerPresenter::~ThumbnailMakerPresenter() {
}