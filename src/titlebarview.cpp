#include "titlebarview.h"

TitlebarView::TitlebarView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void TitlebarView::createUi() {
    setObjectName("TitlebarView");
    setAttribute(Qt::WA_StyledBackground);
    setFixedHeight(40);
}

void TitlebarView::connectSig() {
}