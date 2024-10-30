#include "inc/imageerasepreviewview.h"
#include "inc/signals.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>

namespace imageerase {
ImageErasePreviewView::ImageErasePreviewView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    sigConnect();
}

ImageErasePreviewView::~ImageErasePreviewView() {
}

void ImageErasePreviewView::createUi() {
}

void ImageErasePreviewView::sigConnect() {
}

} // namespace imageerase