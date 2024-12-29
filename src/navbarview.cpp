#include "navbarview.h"

NavbarView::NavbarView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void NavbarView::createUi() {
    setObjectName("NavbarView");
    setAttribute(Qt::WA_StyledBackground);
    setFixedWidth(200);
}

void NavbarView::connectSig() {
}