/*
 * @Author: weick 
 * @Date: 2024-06-03 07:46:21 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-03 07:46:21 
 */

#include "inc/image2gifsettingview.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/alineedit.h"
#include "../awidget/inc/acombobox.h"
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/aradiobutton.h"
#include "inc/models.h"
#include "inc/settings.h"
#include "inc/signals.h"

namespace image2gif {

Image2GifSettingView::Image2GifSettingView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    init();
    sigConnect();
    changeLanguage();
}

Image2GifSettingView::~Image2GifSettingView() {
}

void Image2GifSettingView::createUi() {
    auto mainLayout = new AHBoxLayout(this);

    out_resolution_label_ = new ALabel(this);
    out_resolution_combo_ = new AComboBox(this);
    out_resolution_combo_->setFixedWidth(150);

    mainLayout->addWidget(out_resolution_label_);
    mainLayout->addWidget(out_resolution_combo_);

    out_size_label_ = new ALabel(this);

    mainLayout->addWidget(out_size_label_);

    out_w_edit_validator_ = new QIntValidator(this);
    out_w_edit_validator_->setRange(1, 10000);

    out_w_edit_ = new ALineEdit(this);
    out_w_edit_->setFixedWidth(50);
    out_w_edit_->setValidator(out_w_edit_validator_);

    out_h_edit_validator_ = new QIntValidator(this);
    out_h_edit_validator_->setRange(1, 10000);

    out_h_edit_ = new ALineEdit(this);
    out_h_edit_->setFixedWidth(50);
    out_h_edit_->setValidator(out_h_edit_validator_);

    ALabel *out_size_x_label_ = new ALabel(this);
    out_size_x_label_->setText("x");

    mainLayout->addWidget(out_w_edit_);
    mainLayout->addWidget(out_size_x_label_);
    mainLayout->addWidget(out_h_edit_);
    mainLayout->addSpacing(24);

    out_fps_label_ = new ALabel(this);
    out_fps_combo_ = new AComboBox(this);
    out_fps_combo_->setFixedWidth(50);
    
    mainLayout->addWidget(out_fps_label_);
    mainLayout->addWidget(out_fps_combo_);

    out_quality_label_ = new ALabel(this);
    out_quality_combo_ = new AComboBox(this);
    out_quality_combo_->setFixedWidth(50);

    mainLayout->addWidget(out_quality_label_);
    mainLayout->addWidget(out_quality_combo_);

    out_repeat_radio_ = new ARadioButton(this);
    mainLayout->addWidget(out_repeat_radio_);

    mainLayout->addStretch();

    export_button_ = new APushButton(this);
    export_button_->setFixedHeight(32);

    mainLayout->addWidget(export_button_);
}

void Image2GifSettingView::changeLanguage() {
    out_size_label_->setText(tr("Size"));
    out_fps_label_->setText(tr("Frame Rate"));
    out_quality_label_->setText(tr("Quality"));
    out_repeat_radio_->setText(tr("Repeat"));
    export_button_->setText("Export");
}

void Image2GifSettingView::sigConnect() {
    // connect(out_resolution_combo_, &QComboBox::currentTextChanged, this, &Image2GifSettingView::slotOutResolutionComboCurrentTextChanged);
    // connect(out_w_edit_, &QLineEdit::textChanged, this, &Image2GifSettingView::slotOutWEditTextChanged);
    // connect(out_h_edit_, &QLineEdit::textChanged, this, &Image2GifSettingView::slotOutHEditTextChanged);
    // connect(out_fps_combo_, &QComboBox::currentTextChanged, this, &Image2GifSettingView::slotOutFpsComboCurrentTextChanged);
    // connect(out_quality_combo_, &QComboBox::currentTextChanged, this, &Image2GifSettingView::slotOutQualityComboCurrentTextChanged);
    // connect(out_repeat_radio_, &QRadioButton::toggled, this, &Image2GifSettingView::slotOutRepeatRadioToggled);
    connect(export_button_, &APushButton::clicked, this, &Image2GifSettingView::slotExportButtonClicked);
}

void Image2GifSettingView::init() {
    out_w_edit_->setText(QString::number(SETTINGS->gifWidth()));
    out_h_edit_->setText(QString::number(SETTINGS->gifHeight()));
    out_resolution_combo_->addItems(ImageResolutionDesList());
    out_resolution_combo_->setCurrentText(ImageResolutionDesMap[(ImageResolution)SETTINGS->gifResolution()]);
    out_fps_combo_->addItems(GifFpsDesList());
    out_fps_combo_->setCurrentText(GifFpsDesMap[(GifFps)SETTINGS->gifFps()]);
    out_quality_combo_->addItems(ImageQualityDesList());
    out_quality_combo_->setCurrentText(ImageQualityDesMap[(ImageQuality)SETTINGS->gifQuality()]);
    out_repeat_radio_->setChecked(SETTINGS->gifRepeat());
}

void Image2GifSettingView::slotExportButtonClicked() {
    emit Signals::getInstance()->sigExportStart();
}
} // namespace image2gif