/*
 * @Author: weick 
 * @Date: 2024-06-04 08:01:11 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-04 08:01:11 
 */

#include "inc/imageenhancementsettingview.h"

namespace imageenhancement {

ImageEnhancementSettingView::ImageEnhancementSettingView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

ImageEnhancementSettingView::~ImageEnhancementSettingView() {
}

void ImageEnhancementSettingView::createUi() {
}

void ImageEnhancementSettingView::changeLanguage() {
}

void ImageEnhancementSettingView::sigConnect() {
}
} // namespace imageenhancement