#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class MainPresenter : public Presenter {
public:
    explicit MainPresenter(IView* view, IRepository *repository);
    ~MainPresenter();
};