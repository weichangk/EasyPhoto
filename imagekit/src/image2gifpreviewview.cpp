/*
 * @Author: weick
 * @Date: 2024-03-23 11:13:49
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:50:47
 */

#include "inc/image2gifpreviewview.h"
#include "inc/signals.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/awidget.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"
#include <QTimer>

namespace image2gif {
Image2GifPreviewView::Image2GifPreviewView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

Image2GifPreviewView::~Image2GifPreviewView() {
}

void Image2GifPreviewView::createUi() {
}

void Image2GifPreviewView::changeLanguage() {
}

void Image2GifPreviewView::sigConnect() {
}

} // namespace image2gif