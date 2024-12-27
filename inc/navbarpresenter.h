#pragma once
#include "globalpresenter.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class NavbarPresenter : public Presenter {
public:
    explicit NavbarPresenter(IView* pView);
    ~NavbarPresenter();
};