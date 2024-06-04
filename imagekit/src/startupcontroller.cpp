/*
 * @Author: weick
 * @Date: 2023-12-05 23:03:58
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-04 08:02:56
 */

#include "inc/startupcontroller.h"
#include "inc/startupwindow.h"
#include "inc/signals.h"

StartupController::StartupController() {
    m_StartupWindow = new StartupWindow();
    conversion_Controller_ = new imageconversion::ConversionController();
    compression_controller_ = new imagecompression::CompressionController();
    edit_controller_ = new imageedit::EditController();
    image2gif_controller_ = new image2gif::Image2GifController();
    imageerase_controller_ = new imageerase::ImageEraseController();
    imageenhancement_controller_ = new imageenhancement::ImageEnhancementController();
    sigConnect();
}

StartupController::~StartupController() {
}

void StartupController::showFunc(ImageFunc func) {
    switch (func) {
    case ImageFunc::STARTUP:
        m_StartupWindow->show();
        break;
    case ImageFunc::CONVERSION:
        m_StartupWindow->close();
        conversion_Controller_->showWindow();
        break;
    case ImageFunc::COMPRESSION:
        m_StartupWindow->close();
        compression_controller_->showWindow();
        break;
    case ImageFunc::EDIT:
        m_StartupWindow->close();
        edit_controller_->showWindow();
        break;
    case ImageFunc::IMAGE2GIF:
        m_StartupWindow->close();
        image2gif_controller_->showWindow();
        break;
    case ImageFunc::ERASE:
        m_StartupWindow->close();
        imageerase_controller_->showWindow();
        break;
    case ImageFunc::ENHANCEMENT:
        m_StartupWindow->close();
        imageenhancement_controller_->showWindow();
        break;
    default:
        break;
    }
}

void StartupController::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigGotoFunc, this, &StartupController::showFunc);
}
