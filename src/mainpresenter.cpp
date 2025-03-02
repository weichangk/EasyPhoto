#include "mainpresenter.h"
#include "mainview.h"
#include "mainrepository.h"
#include "titlebarfuncmessage.h"

MainPresenter::MainPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
    MainView *mainView = dynamic_cast<MainView *>(view);
    MainRepository *mainRepository = dynamic_cast<MainRepository *>(repository);
    if (mainView && mainRepository) {
        m_pTitlebarPresenter = new TitlebarPresenter(mainView->titlebarView(), mainRepository->titlebarRepository());
        m_pNavbarPresenter = new NavbarPresenter(mainView->navbarView(), mainRepository->navbarRepository());
        m_pFuncAreaPresenter = new FuncAreaPresenter(mainView->funcAreaView(), mainRepository->funcAreaRepository());

        m_pNavbarPresenter->funcChangeSubjectAttach(m_pFuncAreaPresenter);
        m_pFuncAreaPresenter->homePresente()->funcChangeSubjectAttach(m_pFuncAreaPresenter);
        m_pFuncAreaPresenter->homePresente()->navbarCheckedSubjectAttach(m_pNavbarPresenter);
        m_pTitlebarPresenter->titlebarFuncSubjectAttach(this);
    }
}

MainPresenter::~MainPresenter() {
}

void MainPresenter::titleBarFuncHandle(ETitleBarFunc func) {
    TitlebarFuncMessage msg(func);
    view()->sendMessage(&msg);
}