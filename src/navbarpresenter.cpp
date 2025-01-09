#include "navbarpresenter.h"
#include "navbarmessage.h"

NavbarPresenter::NavbarPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

NavbarPresenter::~NavbarPresenter() {
}

bool NavbarPresenter::handleMessage(IMessage *message) {
    if (NavChangeMessage *msg = dynamic_cast<NavChangeMessage *>(message)) {
    }
    return false;
}
