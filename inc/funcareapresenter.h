#pragma once
#include "globalpresenter.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class FuncAreaPresenter : public Presenter {
public:
    explicit FuncAreaPresenter(IView* pView);
    ~FuncAreaPresenter();
};