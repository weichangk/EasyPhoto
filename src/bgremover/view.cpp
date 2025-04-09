#include "bgremover/view.h"

BackgroungRemoverView::BackgroungRemoverView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void BackgroungRemoverView::createUi() {
    setObjectName("BackgroungRemoverView");
    setAttribute(Qt::WA_StyledBackground);

    QLabel *label = new QLabel("BackgroungRemoverView", this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(label, 0, Qt::AlignCenter);
}

void BackgroungRemoverView::connectSig() {
}