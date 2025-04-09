#include "downloader/presenter.h"

DownloaderPresenter::DownloaderPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

DownloaderPresenter::~DownloaderPresenter() {
}