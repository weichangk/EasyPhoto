#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"

using namespace QtmMvp;

class DownloaderPresenter : public Presenter {
public:
    explicit DownloaderPresenter(IView* view, IRepository *repository);
    ~DownloaderPresenter();
};