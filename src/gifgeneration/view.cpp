#include "gifgeneration/view.h"

GifGenerationView::GifGenerationView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void GifGenerationView::createUi() {
    setObjectName("GifGenerationView");
    setAttribute(Qt::WA_StyledBackground);

    QLabel *label = new QLabel("GifGenerationView", this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(label, 0, Qt::AlignCenter);
}

void GifGenerationView::connectSig() {
}