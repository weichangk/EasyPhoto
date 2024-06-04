/*
 * @Author: weick 
 * @Date: 2024-06-04 08:01:06 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-04 08:01:06 
 */

#include "inc/imageenhancementpreviewview.h"
#include "inc/signals.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/awidget.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"
#include <QTimer>

namespace imageenhancement {
ImageEnhancementPreviewView::ImageEnhancementPreviewView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

ImageEnhancementPreviewView::~ImageEnhancementPreviewView() {
}

void ImageEnhancementPreviewView::createUi() {
}

void ImageEnhancementPreviewView::changeLanguage() {
}

void ImageEnhancementPreviewView::sigConnect() {
}

} // namespace imageenhancement