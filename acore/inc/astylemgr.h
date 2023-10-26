#pragma once
#include "acore_global.h"

class ACORE_EXPORT AStyleMgr
{
public:
    static void setStyleToApp(const QString &qssFolder);
    static void setStyleToWidget(QWidget *widget, const QString& fileName);
};
