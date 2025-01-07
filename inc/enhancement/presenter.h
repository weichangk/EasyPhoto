#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class EnhancementPresenter : public Presenter {
public:
    explicit EnhancementPresenter(IView* view, IRepository *repository);
    ~EnhancementPresenter();
};