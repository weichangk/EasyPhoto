#include "inpainting/view.h"

InpaintingView::InpaintingView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void InpaintingView::createUi() {
    setObjectName("InpaintingView");
    setAttribute(Qt::WA_StyledBackground);
}

void InpaintingView::connectSig() {
}