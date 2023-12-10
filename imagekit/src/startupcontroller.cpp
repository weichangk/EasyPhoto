/*
 * @Author: weick
 * @Date: 2023-12-05 23:03:58
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-10 15:00:14
 */

#include "inc/startupcontroller.h"
#include "inc/startupwindow.h"
#include "inc/signals.h"

StartupController::StartupController() {
    m_StartupWindow = new StartupWindow();
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
        if (!m_ConversionWindow) {
            m_ConversionWindow = new ConversionWindow;
        }
        m_StartupWindow->close();
        m_ConversionWindow->show();
        break;
    case Models::Funcs::ImageCompression:
        if (!m_CompressionWindow) {
            m_CompressionWindow = new CompressionWindow;
        }
        m_StartupWindow->close();
        m_CompressionWindow->show();
        break;
    default:
        break;
    }
}

void StartupController::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigGotoFunc, this, &StartupController::showFunc);
}
