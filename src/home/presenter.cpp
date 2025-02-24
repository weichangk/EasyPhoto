#include "home/presenter.h"
#include "home/repository.h"

HomePresenter::HomePresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

HomePresenter::~HomePresenter() {
}

QList<SFuncItemData> HomePresenter::datas() {
    HomeRepository *rep = dynamic_cast<HomeRepository *>(repository());
    return rep->datas();
}