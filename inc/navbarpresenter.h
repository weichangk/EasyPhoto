#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class NavbarPresenter : public Presenter {
public:
    explicit NavbarPresenter(IView* view, IRepository *repository);
    ~NavbarPresenter();
};