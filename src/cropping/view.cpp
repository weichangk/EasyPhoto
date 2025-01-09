#include "cropping/view.h"

CroppingView::CroppingView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void CroppingView::createUi() {
    setObjectName("CroppingView");
    setAttribute(Qt::WA_StyledBackground);

    QLabel *label = new QLabel("CroppingView", this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(label, 0, Qt::AlignCenter);
}

void CroppingView::connectSig() {
}