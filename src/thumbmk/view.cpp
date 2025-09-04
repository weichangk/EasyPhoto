#include "thumbmk/view.h"

ThumbMkView::ThumbMkView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void ThumbMkView::createUi() {
    setObjectName("ThumbMkView");
    setAttribute(Qt::WA_StyledBackground);

    QLabel *label = new QLabel("ThumbMkView", this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(label, 0, Qt::AlignCenter);
}

void ThumbMkView::connectSig() {
}