/*
 * @Author: weick
 * @Date: 2023-12-05 23:02:29
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:02:29
 */

#pragma once
#include "startupwindow.h"
#include <QObject>

class StartupController : public QObject {
    Q_OBJECT
public:
    StartupController();
    ~StartupController();
    void show();

private:
    void initImageFunc();

private:
    StartupWindow *m_StartupWindow = nullptr;
};
