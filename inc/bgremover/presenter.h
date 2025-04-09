#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class BackgroungRemoverPresenter : public Presenter {
public:
    explicit BackgroungRemoverPresenter(IView* view, IRepository *repository);
    ~BackgroungRemoverPresenter();
};