#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class TitlebarPresenter : public Presenter {
public:
    explicit TitlebarPresenter(IView* view, IRepository *repository);
    ~TitlebarPresenter();
};