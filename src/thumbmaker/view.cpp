#include "thumbmaker/view.h"

ThumbnailMakerView::ThumbnailMakerView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void ThumbnailMakerView::createUi() {
    setObjectName("ThumbnailMakerView");
    setAttribute(Qt::WA_StyledBackground);

    QLabel *label = new QLabel("ThumbnailMakerView", this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(label, 0, Qt::AlignCenter);
}

void ThumbnailMakerView::connectSig() {
}