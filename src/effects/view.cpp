#include "effects/view.h"

EffectsView::EffectsView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void EffectsView::createUi() {
    setObjectName("EffectsView");
    setAttribute(Qt::WA_StyledBackground);

    QLabel *label = new QLabel("EffectsView", this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(label, 0, Qt::AlignCenter);
}

void EffectsView::connectSig() {
}