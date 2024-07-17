/*
 * @Author: weick 
 * @Date: 2024-06-03 07:46:21 
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-18 07:45:22
 */

#include "inc/image2gifsettingview.h"
#include "../acore/inc/aobjecthelper.h"
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

    resolution_label_ = new ALabel(this);
    resolution_combo_ = new AComboBox(this);
    resolution_combo_->setFixedWidth(150);

    mainLayout->addWidget(resolution_label_);
    mainLayout->addWidget(resolution_combo_);

    size_label_ = new ALabel(this);

    mainLayout->addWidget(size_label_);

    w_edit_validator_ = new QIntValidator(this);
    w_edit_validator_->setRange(1, 10000);

    w_edit_ = new ALineEdit(this);
    w_edit_->setFixedWidth(50);
    w_edit_->setValidator(w_edit_validator_);

    h_edit_validator_ = new QIntValidator(this);
    h_edit_validator_->setRange(1, 10000);

    h_edit_ = new ALineEdit(this);
    h_edit_->setFixedWidth(50);
    h_edit_->setValidator(h_edit_validator_);

    ALabel *size_x_label_ = new ALabel(this);
    size_x_label_->setText("x");

    mainLayout->addWidget(w_edit_);
    mainLayout->addWidget(size_x_label_);
    mainLayout->addWidget(h_edit_);
    mainLayout->addSpacing(24);

    fps_label_ = new ALabel(this);
    fps_combo_ = new AComboBox(this);
    fps_combo_->setFixedWidth(50);
    
    mainLayout->addWidget(fps_label_);
    mainLayout->addWidget(fps_combo_);

    quality_label_ = new ALabel(this);
    quality_combo_ = new AComboBox(this);
    quality_combo_->setFixedWidth(50);

    mainLayout->addWidget(quality_label_);
    mainLayout->addWidget(quality_combo_);

    repeat_radio_ = new ARadioButton(this);
    mainLayout->addWidget(repeat_radio_);

    mainLayout->addStretch();

    export_button_ = new APushButton(this);
    export_button_->setFixedHeight(32);

    mainLayout->addWidget(export_button_);
}

void Image2GifSettingView::changeLanguage() {
    size_label_->setText(tr("Size"));
    fps_label_->setText(tr("Frame Rate"));
    quality_label_->setText(tr("Quality"));
    repeat_radio_->setText(tr("Repeat"));
    export_button_->setText("Export");
}

void Image2GifSettingView::sigConnect() {
    connect(resolution_combo_, &QComboBox::currentTextChanged, this, &Image2GifSettingView::slotResolutionComboCurrentTextChanged);
    connect(w_edit_, &QLineEdit::textChanged, this, &Image2GifSettingView::slotWEditTextChanged);
    connect(h_edit_, &QLineEdit::textChanged, this, &Image2GifSettingView::slotHEditTextChanged);
    connect(fps_combo_, &QComboBox::currentTextChanged, this, &Image2GifSettingView::slotFpsComboCurrentTextChanged);
    connect(quality_combo_, &QComboBox::currentTextChanged, this, &Image2GifSettingView::slotQualityComboCurrentTextChanged);
    connect(repeat_radio_, &QRadioButton::toggled, this, &Image2GifSettingView::slotRepeatRadioToggled);
    connect(export_button_, &APushButton::clicked, this, &Image2GifSettingView::slotExportButtonClicked);
}

void Image2GifSettingView::init() {
    w_edit_->setText(QString::number(SETTINGS->gifWidth()));
    h_edit_->setText(QString::number(SETTINGS->gifHeight()));
    resolution_combo_->addItems(ImageResolutionDesList());
    resolution_combo_->setCurrentText(ImageResolutionDesMap[(ImageResolution)SETTINGS->gifResolution()]);
    setWHEditEnabled(SETTINGS->gifResolution() == ImageResolution::Custom);
    fps_combo_->addItems(GifFpsDesList());
    fps_combo_->setCurrentText(GifFpsDesMap[(GifFps)SETTINGS->gifFps()]);
    quality_combo_->addItems(ImageQualityDesList());
    quality_combo_->setCurrentText(ImageQualityDesMap[(ImageQuality)SETTINGS->gifQuality()]);
    repeat_radio_->setChecked(SETTINGS->gifRepeat());
}

void Image2GifSettingView::setWHEditEnabled(bool enable) {
    w_edit_->setEnabled(enable);
    h_edit_->setEnabled(enable);
}

void Image2GifSettingView::slotExportButtonClicked() {
    emit Signals::getInstance()->sigExportStart();
}

void Image2GifSettingView::slotResolutionComboCurrentTextChanged(const QString &text) {
    auto resolution = ImageResolutionDesMap.key(text);
    SETTINGS->setGifResolution(resolution);
    setWHEditEnabled(resolution == ImageResolution::Custom);
    if(resolution != ImageResolution::Custom) {
        SETTINGS->setGifWidth(ImageResolutionSizeMap.value(resolution).width());
        SETTINGS->setGifHeight(ImageResolutionSizeMap.value(resolution).height());
        blockSignalsFunc(w_edit_, [&] { w_edit_->setText(QString::number(SETTINGS->gifWidth())); });
        blockSignalsFunc(h_edit_, [&] { h_edit_->setText(QString::number(SETTINGS->gifHeight())); });
    }
}

void Image2GifSettingView::slotWEditTextChanged(const QString &text) {
    SETTINGS->setGifWidth(text.toInt());
}

void Image2GifSettingView::slotHEditTextChanged(const QString &text) {
    SETTINGS->setGifHeight(text.toInt());
}

void Image2GifSettingView::slotFpsComboCurrentTextChanged(const QString &text) {
    SETTINGS->setGifFps(GifFpsDesMap.key(text));
}

void Image2GifSettingView::slotQualityComboCurrentTextChanged(const QString &text) {
    SETTINGS->setGifQuality(ImageQualityDesMap.key(text));
}

void Image2GifSettingView::slotRepeatRadioToggled(bool checked) {
    SETTINGS->setGifRepeat(checked);
}
} // namespace image2gif