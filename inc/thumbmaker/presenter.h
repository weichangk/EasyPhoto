#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class ThumbnailMakerPresenter : public Presenter {
public:
    explicit ThumbnailMakerPresenter(IView* view, IRepository *repository);
    ~ThumbnailMakerPresenter();
};