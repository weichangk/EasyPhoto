#include "compression/presenter.h"

CompressionPresenter::CompressionPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

CompressionPresenter::~CompressionPresenter() {
}