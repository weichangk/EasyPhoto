#include "mainpresenter.h"

MainPresenter::MainPresenter(IView *pView) :
    Presenter(pView) {
}

MainPresenter::~MainPresenter() {
    qDebug() << "MainPresenter::~MainPresenter()";
}