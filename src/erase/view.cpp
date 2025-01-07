#include "erase/view.h"

EraseView::EraseView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void EraseView::createUi() {
    setObjectName("EraseView");
    setAttribute(Qt::WA_StyledBackground);
}

void EraseView::connectSig() {
}