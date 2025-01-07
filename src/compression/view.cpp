#include "compression/view.h"

CompressionView::CompressionView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void CompressionView::createUi() {
    setObjectName("CompressionView");
    setAttribute(Qt::WA_StyledBackground);
}

void CompressionView::connectSig() {
}