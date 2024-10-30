#include "inc/imageupscaylstepview.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

namespace imageupscayl {

ImageUpscaylStepView::ImageUpscaylStepView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    sigConnect();
}

ImageUpscaylStepView::~ImageUpscaylStepView() {
}

void ImageUpscaylStepView::createUi() {
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);

    step1_lab_ = new QLabel(this);
    mainLayout->addWidget(step1_lab_);

    select_image_btn_ = new QPushButton(this);
    mainLayout->addWidget(select_image_btn_);

    step2_lab_ = new QLabel(this);
    mainLayout->addWidget(step2_lab_);

    select_model_lab_ = new QLabel(this);
    mainLayout->addWidget(select_model_lab_);

    select_model_cmb_ = new QComboBox(this);
    mainLayout->addWidget(select_model_cmb_);

    step3_lab_ = new QLabel(this);
    mainLayout->addWidget(step3_lab_);

    select_scale_lab_ = new QLabel(this);
    mainLayout->addWidget(select_scale_lab_);

    select_scale_sld_ = new QSlider(this);
    mainLayout->addWidget(select_scale_sld_);

    step4_lab_ = new QLabel(this);
    mainLayout->addWidget(step4_lab_);

    select_output_folder_lab_ = new QLabel(this);
    mainLayout->addWidget(select_output_folder_lab_);

    select_output_folder_btn_ = new QPushButton(this);
    mainLayout->addWidget(select_output_folder_btn_);

    step5_lab_ = new QLabel(this);
    mainLayout->addWidget(step5_lab_);

    upscayl_btn_ = new QPushButton(this);
    mainLayout->addWidget(upscayl_btn_);

    mainLayout->addStretch();

    //
    step1_lab_->setText(tr("Step 1"));
    select_image_btn_->setText(tr("Select Image"));
    step2_lab_->setText(tr("Step 2"));
    select_model_lab_->setText(tr("Select Model"));
    step3_lab_->setText(tr("Step 3"));
    select_scale_lab_->setText(tr("Select Scale"));
    step4_lab_->setText(tr("Step 4"));
    select_output_folder_lab_->setText(tr("Select Output Folder"));
    select_output_folder_btn_->setText(tr("Select Folder"));
    step5_lab_->setText(tr("Step 5"));
    upscayl_btn_->setText(tr("Upscale"));
}

void ImageUpscaylStepView::sigConnect() {
}
} // namespace imageupscayl