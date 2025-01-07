#include "erase/presenter.h"

ErasePresenter::ErasePresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

ErasePresenter::~ErasePresenter() {
}