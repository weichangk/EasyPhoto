/*
 * @Author: weick 
 * @Date: 2024-06-03 07:39:05 
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-18 07:42:40
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
    void init();
    void setWHEditEnabled(bool enable);
    void slotExportButtonClicked();
    void slotResolutionComboCurrentTextChanged(const QString &text);
    void slotWEditingConfirm(const QString &text);
    void slotHEditingConfirm(const QString &text);
    void slotFpsComboCurrentTextChanged(const QString &text);
    void slotQualityComboCurrentTextChanged(const QString &text);
    void slotRepeatRadioToggled(bool checked);
    
private:
    ALabel *resolution_label_;
    AComboBox *resolution_combo_;
    ALabel *size_label_;
    ALineEdit *w_edit_;
    ALineEdit *h_edit_;
    QIntValidator *w_edit_validator_;
    QIntValidator *h_edit_validator_;
    ALabel *fps_label_;
    AComboBox *fps_combo_;
    ALabel *quality_label_;
    AComboBox *quality_combo_;
    ARadioButton *repeat_radio_;
    APushButton *export_button_;
};
} // namespace image2gif