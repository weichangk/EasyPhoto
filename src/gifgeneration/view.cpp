#include "gifgeneration/view.h"

GifGenerationView::GifGenerationView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void GifGenerationView::createUi() {
    setObjectName("GifGenerationView");
    setAttribute(Qt::WA_StyledBackground);
}

void GifGenerationView::connectSig() {
}