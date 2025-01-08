#include "gifgeneration/presenter.h"

GifGenerationPresenter::GifGenerationPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

GifGenerationPresenter::~GifGenerationPresenter() {
}