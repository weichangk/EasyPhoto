/*
 * @Author: weick
 * @Date: 2024-07-23 07:25:20
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-23 07:54:43
 */

#pragma once
#include "../agui/inc/abasewidget.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/acombobox.h"
#include "../awidget/inc/aradiobutton.h"
#include "../awidget/inc/aslider.h"

namespace imageupscayl {
class ImageUpscaylStepView : public ABaseWidget {
    Q_OBJECT
public:
    explicit ImageUpscaylStepView(QWidget *parent = nullptr);
    ~ImageUpscaylStepView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    ALabel *step1_lab_ = nullptr;
    APushButton *select_image_btn_ = nullptr;
    APushButton *select_folder_btn_ = nullptr;
    ALabel *step2_lab_ = nullptr;
    ALabel *select_model_lab_ = nullptr;
    AComboBox *select_model_cmb_ = nullptr;
    ALabel *step3_lab_ = nullptr;
    ALabel *select_scale_lab_ = nullptr;
    ASlider *select_scale_sld_ = nullptr;
    ALabel *step4_lab_ = nullptr;
    ALabel *select_output_folder_lab_ = nullptr;
    APushButton *select_output_folder_btn_ = nullptr;
    ALabel *step5_lab_ = nullptr;
    APushButton *upscayl_btn_ = nullptr;
};
} // namespace imageupscayl