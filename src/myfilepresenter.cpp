#include "myfilepresenter.h"

MyFilePresenter::MyFilePresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

MyFilePresenter::~MyFilePresenter() {
}