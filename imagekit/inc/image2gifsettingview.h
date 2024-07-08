/*
 * @Author: weick 
 * @Date: 2024-06-03 07:39:05 
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:43:08
 */

#pragma once
#include "../agui/inc/abasewidget.h"

class ALabel;
class ALineEdit;
class QIntValidator;
class ALineEdit;
class AComboBox;
class APushButton;
class ARadioButton;
namespace image2gif {
class Image2GifSettingView : public ABaseWidget {
    Q_OBJECT
public:
    explicit Image2GifSettingView(QWidget *parent = nullptr);
    ~Image2GifSettingView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    ALabel *out_size_label_;
    ALineEdit *out_w_edit_;
    ALineEdit *out_h_edit_;
    QIntValidator *out_w_edit_validator_;
    QIntValidator *out_h_edit_validator_;
    ALabel *out_fps_label_;
    AComboBox *out_fps_combo_;
    ARadioButton *out_loop_radio_;
    APushButton *export_button_;
};
} // namespace image2gif