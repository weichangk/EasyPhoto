#pragma once
#include "startupwindow.h"
#include <QObject>

class StartupController : public QObject
{
    Q_OBJECT
public:
    StartupController();
    ~StartupController();
    void show();

private:
    void initImageFunc();

private:
    StartupWindow * m_StartupWindow = nullptr;
};
