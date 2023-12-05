/*
 * @Author: weick
 * @Date: 2023-12-05 23:03:42
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:03:42
 */

#include "inc/imagekitwindow.h"

ImageKitWindow::ImageKitWindow(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

ImageKitWindow::~ImageKitWindow() {
}

void ImageKitWindow::createUi() {
    setFixedSize(900, 600);
}

void ImageKitWindow::changeLanguage() {
}

void ImageKitWindow::sigConnect() {
}
