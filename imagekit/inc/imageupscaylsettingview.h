/*
 * @Author: weick 
 * @Date: 2024-06-04 08:00:37 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-04 08:00:37 
 */

#pragma once
#include "../agui/inc/abasewidget.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/aslider.h"

namespace imageupscayl {
class ImageUpscaylSettingView : public ABaseWidget {
    Q_OBJECT
public:
    explicit ImageUpscaylSettingView(QWidget *parent = nullptr);
    ~ImageUpscaylSettingView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    ALabel *model_lab_ = nullptr;
    APushButton *model_btn_ = nullptr;

    ALabel *fmt_lab_ = nullptr;
    APushButton *png_fmt_btn_ = nullptr;
    APushButton *jpg_fmt_btn_ = nullptr;
    APushButton *webp_fmt_btn_ = nullptr;

    ALabel *scale_lab_ = nullptr;
    ASlider *scale_slider_ = nullptr;

    ALabel *compression_lab_ = nullptr;
    ASlider *compression_slider_ = nullptr;

    ALabel *output_folder_lab_ = nullptr;
    APushButton *output_folder_btn_ = nullptr;

    ALabel *reset_lab_ = nullptr;
    APushButton *reset_btn_ = nullptr;
};
} // namespace imageupscayl