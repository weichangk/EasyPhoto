#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class CompressionPresenter : public Presenter {
public:
    explicit CompressionPresenter(IView* view, IRepository *repository);
    ~CompressionPresenter();
};