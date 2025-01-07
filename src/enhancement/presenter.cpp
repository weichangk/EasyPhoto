#include "enhancement/presenter.h"

EnhancementPresenter::EnhancementPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

EnhancementPresenter::~EnhancementPresenter() {
}