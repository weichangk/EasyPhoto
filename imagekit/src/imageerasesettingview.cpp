/*
 * @Author: weick 
 * @Date: 2024-06-03 07:46:21 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-03 07:46:21 
 */

#include "inc/imageerasesettingview.h"

namespace imageerase {

ImageEraseSettingView::ImageEraseSettingView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

ImageEraseSettingView::~ImageEraseSettingView() {
}

void ImageEraseSettingView::createUi() {
}

void ImageEraseSettingView::changeLanguage() {
}

void ImageEraseSettingView::sigConnect() {
}
} // namespace imageerase