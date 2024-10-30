#include "inc/imageupscaylsettingview.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

namespace imageupscayl {

ImageUpscaylSettingView::ImageUpscaylSettingView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    sigConnect();
}

ImageUpscaylSettingView::~ImageUpscaylSettingView() {
}

void ImageUpscaylSettingView::createUi() {
    auto main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0, 0);

    model_lab_ = new QLabel(this);
    main_layout->addWidget(model_lab_);
    model_btn_ = new QPushButton(this);
    main_layout->addWidget(model_btn_);

    fmt_lab_ = new QLabel(this);
    main_layout->addWidget(fmt_lab_);
    auto fmt_layout = new QHBoxLayout(this);
    fmt_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addLayout(fmt_layout);
    png_fmt_btn_ = new QPushButton(this);
    fmt_layout->addWidget(png_fmt_btn_);
    jpg_fmt_btn_ = new QPushButton(this);
    fmt_layout->addWidget(jpg_fmt_btn_);
    webp_fmt_btn_ = new QPushButton(this);
    fmt_layout->addWidget(webp_fmt_btn_);

    scale_lab_ = new QLabel(this);
    main_layout->addWidget(scale_lab_);
    scale_slider_ = new QSlider(Qt::Orientation::Horizontal, this);
    main_layout->addWidget(scale_slider_);

    compression_lab_ = new QLabel(this);
    main_layout->addWidget(compression_lab_);
    compression_slider_ = new QSlider(Qt::Orientation::Horizontal, this);
    main_layout->addWidget(compression_slider_);

    output_folder_lab_ = new QLabel(this);
    main_layout->addWidget(output_folder_lab_);
    output_folder_btn_ = new QPushButton(this);
    main_layout->addWidget(output_folder_btn_);

    reset_lab_ = new QLabel(this);
    main_layout->addWidget(reset_lab_);
    reset_btn_ = new QPushButton(this);
    main_layout->addWidget(reset_btn_);
    
    main_layout->addStretch();

    //
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