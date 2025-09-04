#include "imgdl/view.h"

ImgDlView::ImgDlView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void ImgDlView::createUi() {
    setObjectName("ImgDlView");
    setAttribute(Qt::WA_StyledBackground);

    QLabel *label = new QLabel("ImgDlView", this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(label, 0, Qt::AlignCenter);
}

void ImgDlView::connectSig() {
}