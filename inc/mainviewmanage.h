#pragma once
#include "core/singlton.h"

#include "mainrepository.h"
#include "mainpresenter.h"
#include "mainview.h"

class MainViewManage : public QtmCore::Singlton<MainViewManage> {
public:
    MainViewManage();
    void init(MainRepository *repository, MainView *view, MainPresenter *presenter);
    MainRepository *getMainRepository() const;
    MainView *getMainView() const;
    MainPresenter *getMainPresenter() const;

    void showLoadingMask();
    void hideLoadingMask();

private:
    MainRepository *m_MainRepository = nullptr;
    MainView *m_MainView = nullptr;
    MainPresenter *m_MainPresenter = nullptr;
};

#define MAINVIEWMANAGE MainViewManage::getInstance()