/*
 * @Author: weick 
 * @Date: 2024-06-03 07:46:21 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-03 07:46:21 
 */

#include "inc/image2gifsettingview.h"

namespace image2gif {

Image2GifSettingView::Image2GifSettingView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

Image2GifSettingView::~Image2GifSettingView() {
}

void Image2GifSettingView::createUi() {
}

void Image2GifSettingView::changeLanguage() {
}

void Image2GifSettingView::sigConnect() {
}
} // namespace image2gif