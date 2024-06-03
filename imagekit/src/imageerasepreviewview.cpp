/*
 * @Author: weick
 * @Date: 2024-03-23 11:13:49
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:50:47
 */

#include "inc/imageerasepreviewview.h"
#include "inc/signals.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/awidget.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"
#include <QTimer>

namespace imageerase {
ImageErasePreviewView::ImageErasePreviewView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

ImageErasePreviewView::~ImageErasePreviewView() {
}

void ImageErasePreviewView::createUi() {
}

void ImageErasePreviewView::changeLanguage() {
}

void ImageErasePreviewView::sigConnect() {
}

} // namespace imageerase