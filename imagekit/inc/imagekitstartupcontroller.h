#pragma once
#include "imagekit_global.h"
#include "imagekitstartupwindow.h"

class IMAGEKIT_EXPORT ImageKitStartupController : public QObject
{
    Q_OBJECT
public:
    ImageKitStartupController();
    ~ImageKitStartupController();

    void show();

private:
    void initImageFunc();

private:
    ImageKitStartupWindow * m_ImageKitStartupWindow = nullptr;
};
