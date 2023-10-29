#include "inc/imagekitwindow.h"

ImageKitWindow::ImageKitWindow(QWidget *parent) : ABaseWidget(parent)
{
    createUi();
    sigConnect();
    changeLanguage();
}

ImageKitWindow::~ImageKitWindow()
{
}

void ImageKitWindow::createUi()
{
    setFixedSize(900, 600);
}

void ImageKitWindow::changeLanguage()
{
}

void ImageKitWindow::sigConnect()
{
}
