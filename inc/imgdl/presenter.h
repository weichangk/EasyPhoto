#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace QtmMvp;

class ImgDlPresenter : public Presenter {
public:
    explicit ImgDlPresenter(IView* view, IRepository *repository);
    ~ImgDlPresenter();
};