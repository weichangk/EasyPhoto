/*
 * @Author: weick
 * @Date: 2023-12-05 23:02:29
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-07 23:48:15
 */

#pragma once
#include "startupwindow.h"
#include "models.h"
#include "ConversionController.h"
#include "CompressionController.h"
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
    ConversionController *m_ConversionController = 0;
    CompressionController *m_CompressionController = 0;
};
