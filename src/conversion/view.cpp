#include "conversion/view.h"

ConversionView::ConversionView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void ConversionView::createUi() {
    setObjectName("ConversionView");
    setAttribute(Qt::WA_StyledBackground);
}

void ConversionView::connectSig() {
}