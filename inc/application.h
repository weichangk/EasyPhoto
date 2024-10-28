/*
 * @Author: weick
 * @Date: 2023-12-05 23:01:13
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:01:13
 */

#pragma once
#include <QApplication>

class StartupController;
class Application : public QApplication {
    Q_OBJECT

public:
    Application(int argc, char *argv[]);

private:
    void initUi();

private:
    StartupController *m_StartupController;
};
