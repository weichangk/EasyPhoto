/*
 * @Author: weick
 * @Date: 2023-12-05 23:02:29
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-10 14:57:43
 */

#pragma once
#include "startupwindow.h"
#include "models.h"
#include "conversionwindow.h"
#include "compressionwindow.h"
#include <QObject>

class StartupController : public QObject {
    Q_OBJECT
public:
    explicit StartupController();
    ~StartupController();
    void showFunc(Models::Funcs func);

private:
    void sigConnect();

private:
    StartupWindow *m_StartupWindow = 0;
    ConversionWindow *m_ConversionWindow = 0;
    CompressionWindow *m_CompressionWindow = 0;
};
