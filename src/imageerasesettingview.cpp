#include "inc/imageerasesettingview.h"

namespace imageerase {

ImageEraseSettingView::ImageEraseSettingView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    sigConnect();
}

ImageEraseSettingView::~ImageEraseSettingView() {
}

void ImageEraseSettingView::createUi() {
}

void ImageEraseSettingView::sigConnect() {
}
} // namespace imageerase