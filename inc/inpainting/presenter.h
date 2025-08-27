#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace QtmMvp;

class InpaintingPresenter : public Presenter {
public:
    explicit InpaintingPresenter(IView* view, IRepository *repository);
    ~InpaintingPresenter();
};