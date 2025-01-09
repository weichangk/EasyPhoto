#include "compression/view.h"

CompressionView::CompressionView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void CompressionView::createUi() {
    setObjectName("CompressionView");
    setAttribute(Qt::WA_StyledBackground);

    QLabel *label = new QLabel("CompressionView", this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(label, 0, Qt::AlignCenter);
}

void CompressionView::connectSig() {
}