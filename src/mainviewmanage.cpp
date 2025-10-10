#include "mainviewmanage.h"
#include "widget/loadingmask.h"

MainViewManage::MainViewManage() {
}

void MainViewManage::init(MainRepository *repository, MainView *view, MainPresenter *presenter) {
    m_MainRepository = repository;
    m_MainView = view;
    m_MainPresenter = presenter;

    QtmWidget::LOADINGMASK->setParentWidget(m_MainView);
    QtmWidget::LOADINGMASK->hideIt();
}

MainRepository *MainViewManage::getMainRepository() const {
    return m_MainRepository;
}

MainView *MainViewManage::getMainView() const {
    return m_MainView;
}

MainPresenter *MainViewManage::getMainPresenter() const {
    return m_MainPresenter;
}

void MainViewManage::showLoadingMask() {
    QtmWidget::LOADINGMASK->showIt(QRect(0, 0, m_MainView->width(), m_MainView->height()));
}

void MainViewManage::hideLoadingMask() {
    QtmWidget::LOADINGMASK->hideIt();
}