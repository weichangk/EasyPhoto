/*
 * @Author: weick 
 * @Date: 2024-06-04 08:01:06 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-04 08:01:06 
 */

#include "inc/imageupscaylpreviewview.h"
#include "inc/signals.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/awidget.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"
#include <QTimer>

namespace imageupscayl {
ImageUpscaylPreviewView::ImageUpscaylPreviewView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

ImageUpscaylPreviewView::~ImageUpscaylPreviewView() {
}

void ImageUpscaylPreviewView::createUi() {
}

void ImageUpscaylPreviewView::changeLanguage() {
}

void ImageUpscaylPreviewView::sigConnect() {
}

} // namespace imageupscayl