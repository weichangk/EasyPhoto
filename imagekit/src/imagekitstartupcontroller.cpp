#include "inc/imagekitstartupcontroller.h"

ImageKitStartupController::ImageKitStartupController(ImageKitStartupView * view)
{
    m_view = view;
}

ImageKitStartupController::~ImageKitStartupController()
{
    delete m_view;
}

void ImageKitStartupController::show()
{
    m_view->show();
}
