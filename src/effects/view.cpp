#include "effects/view.h"

EffectsView::EffectsView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void EffectsView::createUi() {
    setObjectName("EffectsView");
    setAttribute(Qt::WA_StyledBackground);
}

void EffectsView::connectSig() {
}