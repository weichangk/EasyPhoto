#include "inc/imageupscaylpreviewview.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

namespace imageupscayl {
ImageUpscaylPreviewView::ImageUpscaylPreviewView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    sigConnect();
}

ImageUpscaylPreviewView::~ImageUpscaylPreviewView() {
}

void ImageUpscaylPreviewView::createUi() {
}

void ImageUpscaylPreviewView::sigConnect() {
}

} // namespace imageupscayl