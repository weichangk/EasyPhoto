#include "inc/imagekitstartupcontroller.h"

ImageKitStartupController::ImageKitStartupController(ImageKitStartupWindow * view)
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
