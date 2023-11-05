#pragma once
#include "imagekit_global.h"
#include "imagekitstartupwindow.h"

class IMAGEKIT_EXPORT ImageKitStartupController : public QObject
{
    Q_OBJECT
public:
    ImageKitStartupController(ImageKitStartupWindow * view);
    ~ImageKitStartupController();

    void show();

private:
    ImageKitStartupWindow * m_view = nullptr;
};
