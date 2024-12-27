#pragma once
#include "globalpresenter.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class TitlebarPresenter : public Presenter {
public:
    explicit TitlebarPresenter(IView* pView);
    ~TitlebarPresenter();
};