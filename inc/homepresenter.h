#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class HomePresenter : public Presenter {
public:
    explicit HomePresenter(IView* view, IRepository *repository);
    ~HomePresenter();
};