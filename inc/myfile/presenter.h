#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace QtmMvp;

class MyFilePresenter : public Presenter {
public:
    explicit MyFilePresenter(IView* view, IRepository *repository);
    ~MyFilePresenter();
};