#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace QtmMvp;

class ThumbMkPresenter : public Presenter {
public:
    explicit ThumbMkPresenter(IView* view, IRepository *repository);
    ~ThumbMkPresenter();
};