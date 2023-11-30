#pragma once

#include "settings.h"
#include <QApplication>


class StartupWindow;
class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int argc, char *argv[]);
    Settings &settings() { return m_Settings; }

private:
    void initUi();
    Settings m_Settings;
    StartupWindow *m_StartupWindow;
};
