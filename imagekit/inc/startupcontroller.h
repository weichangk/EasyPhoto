/*
 * @Author: weick
 * @Date: 2023-12-05 23:02:29
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-04 08:02:04
 */

#pragma once
#include "startupwindow.h"
#include "models.h"
#include "conversioncontroller.h"
#include "compressioncontroller.h"
#include "editcontroller.h"
#include "image2gifcontroller.h"
#include "imageerasecontroller.h"
#include "imageenhancementcontroller.h"
#include <QObject>

class StartupController : public QObject {
    Q_OBJECT
public:
    explicit StartupController();
    ~StartupController();
    void showFunc(ImageFunc func);

private:
    void sigConnect();

private:
    StartupWindow *m_StartupWindow = 0;
    imageconversion::ConversionController *conversion_Controller_ = nullptr;
    imagecompression::CompressionController *compression_controller_ = nullptr;
    imageedit::EditController *edit_controller_ = nullptr;
    image2gif::Image2GifController *image2gif_controller_ = nullptr;
    imageerase::ImageEraseController *imageerase_controller_ = nullptr;
    imageenhancement::ImageEnhancementController *imageenhancement_controller_ = nullptr;
};
