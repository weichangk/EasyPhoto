#include "inpainting/view.h"

InpaintingView::InpaintingView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void InpaintingView::createUi() {
    setObjectName("InpaintingView");
    setAttribute(Qt::WA_StyledBackground);

    QLabel *label = new QLabel("InpaintingView", this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(label, 0, Qt::AlignCenter);
}

void InpaintingView::connectSig() {
}