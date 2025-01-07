#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace qtmaterialmvp;

class ErasePresenter : public Presenter {
public:
    explicit ErasePresenter(IView* view, IRepository *repository);
    ~ErasePresenter();
};