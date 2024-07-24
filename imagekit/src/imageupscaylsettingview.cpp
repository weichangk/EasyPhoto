/*
 * @Author: weick 
 * @Date: 2024-06-04 08:01:11 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-04 08:01:11 
 */

#include "inc/imageupscaylsettingview.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"
namespace imageupscayl {

ImageUpscaylSettingView::ImageUpscaylSettingView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

ImageUpscaylSettingView::~ImageUpscaylSettingView() {
}

void ImageUpscaylSettingView::createUi() {
    auto main_layout = new AVBoxLayout(this);

    model_lab_ = new ALabel(this);
    main_layout->addWidget(model_lab_);
    model_btn_ = new APushButton(this);
    main_layout->addWidget(model_btn_);

    fmt_lab_ = new ALabel(this);
    main_layout->addWidget(fmt_lab_);
    auto fmt_layout = new AHBoxLayout(this);
    main_layout->addLayout(fmt_layout);
    png_fmt_btn_ = new APushButton(this);
    fmt_layout->addWidget(png_fmt_btn_);
    jpg_fmt_btn_ = new APushButton(this);
    fmt_layout->addWidget(jpg_fmt_btn_);
    webp_fmt_btn_ = new APushButton(this);
    fmt_layout->addWidget(webp_fmt_btn_);

    scale_lab_ = new ALabel(this);
    main_layout->addWidget(scale_lab_);
    scale_slider_ = new ASlider(this);
    main_layout->addWidget(scale_slider_);

    compression_lab_ = new ALabel(this);
    main_layout->addWidget(compression_lab_);
    compression_slider_ = new ASlider(this);
    main_layout->addWidget(compression_slider_);

    output_folder_lab_ = new ALabel(this);
    main_layout->addWidget(output_folder_lab_);
    output_folder_btn_ = new APushButton(this);
    main_layout->addWidget(output_folder_btn_);

    reset_lab_ = new ALabel(this);
    main_layout->addWidget(reset_lab_);
    reset_btn_ = new APushButton(this);
    main_layout->addWidget(reset_btn_);
    
    main_layout->addStretch();
}

void ImageUpscaylSettingView::changeLanguage() {
    model_lab_->setText(tr("Select Model"));
    fmt_lab_->setText(tr("Save Image as"));
    png_fmt_btn_->setText(tr("PNG"));
    jpg_fmt_btn_->setText(tr("JPG"));
    webp_fmt_btn_->setText(tr("WEBP"));
    scale_lab_->setText(tr("Image Scale"));
    compression_lab_->setText(tr("Image Compression"));
    output_folder_lab_->setText(tr("Output Folder"));
    reset_lab_->setText(tr("Reset Upscayl"));
    reset_btn_->setText(tr("Reset"));
}

void ImageUpscaylSettingView::sigConnect() {
}
} // namespace imageupscayl