#include "home/presenter.h"

HomePresenter::HomePresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

HomePresenter::~HomePresenter() {
}