#include "mainpresenter.h"

MainPresenter::MainPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

MainPresenter::~MainPresenter() {
    qDebug() << "MainPresenter::~MainPresenter()";
}