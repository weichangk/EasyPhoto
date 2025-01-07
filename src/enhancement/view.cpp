#include "enhancement/view.h"

EnhancementView::EnhancementView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void EnhancementView::createUi() {
    setObjectName("EnhancementView");
    setAttribute(Qt::WA_StyledBackground);
}

void EnhancementView::connectSig() {
}