#include "conversion/presenter.h"

ConversionPresenter::ConversionPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

ConversionPresenter::~ConversionPresenter() {
}