#pragma once
#include "imagekit_global.h"
#include "startupwindow.h"

class ImageKitStartupController : public QObject
{
    Q_OBJECT
public:
    ImageKitStartupController();
    ~ImageKitStartupController();

    void show();

private:
    void initImageFunc();

private:
    StartupWindow * m_StartupWindow = nullptr;
};
