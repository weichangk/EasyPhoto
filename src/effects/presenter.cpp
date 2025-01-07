#include "effects/presenter.h"

EffectsPresenter::EffectsPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

EffectsPresenter::~EffectsPresenter() {
}