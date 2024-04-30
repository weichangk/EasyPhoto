/*
 * @Author: weick
 * @Date: 2024-03-23 11:24:18
 * @Last Modified by: weick
 * @Last Modified time: 2024-04-02 07:49:28
 */

#include "inc/editsettingview.h"
#include "inc/signals.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/atabbar.h"
#include "../awidget/inc/atabwidget.h"
#include "../awidget/inc/awidget.h"
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/acheckbox.h"
#include "../awidget/inc/alineedit.h"
#include "../awidget/inc/aslider.h"
#include "../awidget/inc/aradiobutton.h"
#include <QIntValidator>

namespace imageedit {
EditSettingView::EditSettingView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

EditSettingView::~EditSettingView() {
}

void EditSettingView::createUi() {
    auto mainLayout = new AVBoxLayout(this);
    tab_widget_ = new ATabWidget(this);
    tab_bar_ = new ATabBar(tab_widget_);

    crop_setting_widget_ = new AWidget(this);
    rotate_setting_widget_ = new AWidget(this);
    effect_setting_widget_ = new AWidget(this);
    watermark_setting_widget_ = new AWidget(this);

    tab_widget_->addTab(crop_setting_widget_, "Crop");
    tab_widget_->addTab(rotate_setting_widget_, "Rotate");
    tab_widget_->addTab(effect_setting_widget_, "Effect");
    tab_widget_->addTab(watermark_setting_widget_, "Watermark");

    QIntValidator *cropWEditValidator = new QIntValidator(this);
    QIntValidator *cropHEditValidator = new QIntValidator(this);
    cropWEditValidator->setRange(kCropRectMinW, 1920);
    cropHEditValidator->setRange(kCropRectMinH, 1080);

    original_ratio_label_ = new ALabel(crop_setting_widget_);
    original_ratio_value_label_ = new ALabel(crop_setting_widget_);
    equal_ratio_checkbox_ = new ACheckBox(crop_setting_widget_);
    crop_ratio_label_ = new ALabel(crop_setting_widget_);
    crop_ratio_width_edit_ = new ALineEdit(crop_setting_widget_);
    crop_ratio_height_edit_ = new ALineEdit(crop_setting_widget_);
    crop_ratio_width_edit_->setValidator(cropWEditValidator);
    crop_ratio_height_edit_->setValidator(cropHEditValidator);
    crop_align_center_button_ = new APushButton(crop_setting_widget_);
    crop_reset_button_ = new APushButton(crop_setting_widget_);
    auto crop_layout = new AVBoxLayout(crop_setting_widget_);
    auto original_ratio_layout = new AHBoxLayout();
    original_ratio_layout->addWidget(original_ratio_label_);
    original_ratio_layout->addWidget(original_ratio_value_label_);
    original_ratio_layout->addStretch();
    crop_layout->addLayout(original_ratio_layout);
    crop_layout->addWidget(equal_ratio_checkbox_);
    crop_layout->addWidget(crop_ratio_label_);
    auto crop_ratio_layout = new AHBoxLayout();
    crop_ratio_layout->addWidget(crop_ratio_width_edit_);
    ALabel *x_label = new ALabel(crop_setting_widget_);
    x_label->setText("x");
    crop_ratio_layout->addWidget(x_label);
    crop_ratio_layout->addWidget(crop_ratio_height_edit_);
    crop_ratio_layout->addStretch();
    crop_layout->addLayout(crop_ratio_layout);
    crop_layout->addWidget(crop_align_center_button_);
    crop_layout->addWidget(crop_reset_button_);
    crop_layout->addStretch();

    rotate_right90_button_ = new APushButton(rotate_setting_widget_);
    rotate_left90_button_ = new APushButton(rotate_setting_widget_);
    rotate_horizontal_flip_button_ = new APushButton(rotate_setting_widget_);
    rotate_vertical_flip_button_ = new APushButton(rotate_setting_widget_);
    rotate_angle_label_ = new ALabel(rotate_setting_widget_);
    rotate_angle_edit_ = new ALineEdit(rotate_setting_widget_);
    rotate_reset_button_ = new APushButton(rotate_setting_widget_);
    auto rotate_layout = new AVBoxLayout(rotate_setting_widget_);
    auto rotate_button_layout = new AHBoxLayout();
    rotate_button_layout->addWidget(rotate_right90_button_);
    rotate_button_layout->addWidget(rotate_left90_button_);
    rotate_button_layout->addWidget(rotate_horizontal_flip_button_);
    rotate_button_layout->addWidget(rotate_vertical_flip_button_);
    rotate_button_layout->addStretch();
    rotate_layout->addLayout(rotate_button_layout);
    auto rotate_angle_layout = new AHBoxLayout();
    rotate_angle_layout->addWidget(rotate_angle_label_);
    rotate_angle_layout->addWidget(rotate_angle_edit_);
    rotate_angle_layout->addStretch();
    rotate_layout->addLayout(rotate_angle_layout);
    rotate_layout->addWidget(rotate_reset_button_);
    rotate_layout->addStretch();

    luminance_label_ = new ALabel(effect_setting_widget_);
    luminance_slider_ = new ASlider(effect_setting_widget_);
    luminance_slider_->setOrientation(Qt::Horizontal);
    contrast_label_ = new ALabel(effect_setting_widget_);
    contrast_slider_ = new ASlider(effect_setting_widget_);
    contrast_slider_->setOrientation(Qt::Horizontal);
    saturation_label_ = new ALabel(effect_setting_widget_);
    saturation_slider_ = new ASlider(effect_setting_widget_);
    saturation_slider_->setOrientation(Qt::Horizontal);
    auto effect_layout = new AVBoxLayout(effect_setting_widget_);
    auto luminance_layout = new AHBoxLayout();
    luminance_layout->addWidget(luminance_label_);
    luminance_layout->addWidget(luminance_slider_);
    luminance_layout->addStretch();
    effect_layout->addLayout(luminance_layout);
    auto contrast_layout = new AHBoxLayout();
    contrast_layout->addWidget(contrast_label_);
    contrast_layout->addWidget(contrast_slider_);
    contrast_layout->addStretch();
    effect_layout->addLayout(contrast_layout);
    auto saturation_layout = new AHBoxLayout();
    saturation_layout->addWidget(saturation_label_);
    saturation_layout->addWidget(saturation_slider_);
    saturation_layout->addStretch();
    effect_layout->addLayout(saturation_layout);
    effect_layout->addStretch();

    picture_radio_button_ = new ARadioButton(watermark_setting_widget_);
    picture_path_edit_ = new ALineEdit(watermark_setting_widget_);
    picture_select_button_ = new APushButton(watermark_setting_widget_);
    text_radio_button_ = new ARadioButton(watermark_setting_widget_);
    text_edit_ = new ALineEdit(watermark_setting_widget_);
    text_select_button_ = new APushButton(watermark_setting_widget_);
    mosaic_radio_button_ = new ARadioButton(watermark_setting_widget_);
    mosaic_type1_button_ = new APushButton(watermark_setting_widget_);
    mosaic_type2_button_ = new APushButton(watermark_setting_widget_);
    mosaic_type3_button_ = new APushButton(watermark_setting_widget_);
    none_radio_button_ = new ARadioButton(watermark_setting_widget_);
    auto watermark_layout = new AVBoxLayout(watermark_setting_widget_);
    watermark_layout->addWidget(picture_radio_button_);
    auto picture_layout = new AHBoxLayout();
    picture_layout->addWidget(picture_path_edit_);
    picture_layout->addWidget(picture_select_button_);
    picture_layout->addStretch();
    watermark_layout->addLayout(picture_layout);
    watermark_layout->addWidget(text_radio_button_);
    auto text_layout = new AHBoxLayout();
    text_layout->addWidget(text_edit_);
    text_layout->addWidget(text_select_button_);
    text_layout->addStretch();
    watermark_layout->addLayout(text_layout);
    watermark_layout->addWidget(mosaic_radio_button_);
    auto mosaic_layout = new AHBoxLayout();
    mosaic_layout->addWidget(mosaic_type1_button_);
    mosaic_layout->addWidget(mosaic_type2_button_);
    mosaic_layout->addWidget(mosaic_type3_button_);
    mosaic_layout->addStretch();
    watermark_layout->addLayout(mosaic_layout);
    watermark_layout->addWidget(none_radio_button_);
    watermark_layout->addStretch();

    export_button_ = new APushButton(this);
    export_button_->setFixedHeight(32);
    mainLayout->addWidget(tab_widget_, 1);
    mainLayout->addWidget(export_button_);
}

void EditSettingView::changeLanguage() {
    original_ratio_label_->setText("Original ratio");
    original_ratio_value_label_->setText("1:1");
    equal_ratio_checkbox_->setText("Equal ratio");
    crop_ratio_label_->setText("Crop ratio");
    crop_ratio_width_edit_->setText("1");
    crop_ratio_height_edit_->setText("1");
    crop_align_center_button_->setText("Align center");
    crop_reset_button_->setText("Reset");

    rotate_angle_label_->setText("Angle");
    rotate_angle_edit_->setText("0");
    rotate_reset_button_->setText("Reset");

    luminance_label_->setText("Luminance");
    contrast_label_->setText("Contrast");
    saturation_label_->setText("Saturation");

    picture_radio_button_->setText("Picture");
    text_radio_button_->setText("Text");
    mosaic_radio_button_->setText("Mosaic");
    none_radio_button_->setText("None");

    export_button_->setText("Export");
}

void EditSettingView::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigListItemDataSelected, this, &EditSettingView::preViewDataSelected);
    connect(Signals::getInstance(), &Signals::sigChangedSelectRect2Setting, this, &EditSettingView::selectRectChanged);
    connect(crop_ratio_width_edit_, &ALineEdit::sigEditingConfirm, this, &EditSettingView::cropWidthEditingConfirm);
    connect(crop_ratio_height_edit_, &ALineEdit::sigEditingConfirm, this, &EditSettingView::cropHeightEditingConfirm);
}

void EditSettingView::preViewDataSelected(Data *data) {
    data_ = data;
    equal_ratio_checkbox_->setChecked(data_->is_equal_ratio_crop_);
}

void EditSettingView::selectRectChanged(const QRect &rect) {
    select_rect_ = rect;
    crop_ratio_width_edit_->setText(QString::number(rect.width()));
    crop_ratio_height_edit_->setText(QString::number(rect.height()));
}

void EditSettingView::cropWidthEditingConfirm(const QString text) {
    if (text.toInt() < kCropRectMinW) {
        crop_ratio_width_edit_->setText(QString::number(kCropRectMinW));
    }
    int w = crop_ratio_width_edit_->text().toInt();
    data_->crop_rect.setWidth(w);
    select_rect_.setWidth(w);
    emit Signals::getInstance()->sigChangedSelectRect2Preview(select_rect_);
}

void EditSettingView::cropHeightEditingConfirm(const QString text) {
    if (text.toInt() < kCropRectMinH) {
        crop_ratio_height_edit_->setText(QString::number(kCropRectMinH));
    }
    int h = crop_ratio_height_edit_->text().toInt();
    data_->crop_rect.setHeight(h);
    select_rect_.setHeight(h);
    emit Signals::getInstance()->sigChangedSelectRect2Preview(select_rect_);
}

} // namespace imageedit