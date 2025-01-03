#include "mainpresenter.h"

MainPresenter::MainPresenter(IView *pView) :
    Presenter(pView, nullptr) {
}

MainPresenter::~MainPresenter() {
    qDebug() << "MainPresenter::~MainPresenter()";
}