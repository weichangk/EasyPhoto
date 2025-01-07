#include "cropping/view.h"

CroppingView::CroppingView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void CroppingView::createUi() {
    setObjectName("CroppingView");
    setAttribute(Qt::WA_StyledBackground);
}

void CroppingView::connectSig() {
}