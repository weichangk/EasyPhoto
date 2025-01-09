#include "erase/view.h"

EraseView::EraseView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void EraseView::createUi() {
    setObjectName("EraseView");
    setAttribute(Qt::WA_StyledBackground);

    QLabel *label = new QLabel("EraseView", this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(label, 0, Qt::AlignCenter);
}

void EraseView::connectSig() {
}