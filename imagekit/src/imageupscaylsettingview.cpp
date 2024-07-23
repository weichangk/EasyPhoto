/*
 * @Author: weick 
 * @Date: 2024-06-04 08:01:11 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-04 08:01:11 
 */

#include "inc/imageupscaylsettingview.h"

namespace imageupscayl {

ImageUpscaylSettingView::ImageUpscaylSettingView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

ImageUpscaylSettingView::~ImageUpscaylSettingView() {
}

void ImageUpscaylSettingView::createUi() {
}

void ImageUpscaylSettingView::changeLanguage() {
}

void ImageUpscaylSettingView::sigConnect() {
}
} // namespace imageupscayl