/*
 * @Author: weick
 * @Date: 2023-12-05 23:03:58
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-07 23:48:31
 */

#include "inc/startupcontroller.h"
#include "inc/startupwindow.h"
#include "inc/signals.h"

StartupController::StartupController() {
    m_StartupWindow = new StartupWindow();
    m_ConversionController = new ConversionController();
    m_CompressionController = new CompressionController();
    sigConnect();
}

StartupController::~StartupController() {
}

void StartupController::showFunc(Models::Funcs func) {
    switch (func) {
    case Models::Funcs::Startup:
        m_StartupWindow->show();
        break;
    case Models::Funcs::ImageConversion:
        m_StartupWindow->close();
        m_ConversionController->showWindow();
        break;
    case Models::Funcs::ImageCompression:
        m_StartupWindow->close();
        m_CompressionController->showWindow();
        break;
    default:
        break;
    }
}

void StartupController::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigGotoFunc, this, &StartupController::showFunc);
}
