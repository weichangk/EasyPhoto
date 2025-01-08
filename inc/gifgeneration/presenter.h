#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class GifGenerationPresenter : public Presenter {
public:
    explicit GifGenerationPresenter(IView* view, IRepository *repository);
    ~GifGenerationPresenter();
};