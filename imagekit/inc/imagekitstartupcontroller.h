#pragma once
#include "imagekit_global.h"
#include "imagekitstartupview.h"

class IMAGEKIT_EXPORT ImageKitStartupController : public QObject
{
    Q_OBJECT
public:
    ImageKitStartupController(ImageKitStartupView * view);
    ~ImageKitStartupController();

    void show();

private:
    ImageKitStartupView * m_view = nullptr;
};
