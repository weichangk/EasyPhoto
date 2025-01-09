#include "navbarpresenter.h"
#include "navbarmessage.h"

NavbarPresenter::NavbarPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
}

NavbarPresenter::~NavbarPresenter() {
}

void NavbarPresenter::attach(INavbarObserver *observer) {
    m_pNavbarObserver.attach(observer);
}

void NavbarPresenter::detach(INavbarObserver *observer) {
    m_pNavbarObserver.detach(observer);
}

void NavbarPresenter::notifyNavChange(EFunc func) {
    m_pNavbarObserver.notify(&INavbarObserver::navChange, func);
}

bool NavbarPresenter::handleMessage(IMessage *message) {
    if (NavChangeMessage *msg = dynamic_cast<NavChangeMessage *>(message)) {
        notifyNavChange((EFunc)msg->code());
    }
    return false;
}
