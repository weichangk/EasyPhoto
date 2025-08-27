#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace QtmMvp;

class EffectsPresenter : public Presenter {
public:
    explicit EffectsPresenter(IView* view, IRepository *repository);
    ~EffectsPresenter();
};