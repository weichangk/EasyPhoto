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

namespace image2gif {

Image2GifSettingView::Image2GifSettingView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

Image2GifSettingView::~Image2GifSettingView() {
}

void Image2GifSettingView::createUi() {
    auto mainLayout = new AHBoxLayout(this);

    out_size_label_ = new ALabel(this);

    mainLayout->addWidget(out_size_label_);

    out_w_edit_validator_ = new QIntValidator(this);
    out_w_edit_validator_->setRange(1, 10000);

    out_w_edit_ = new ALineEdit(this);
    out_w_edit_->setFixedWidth(100);
    out_w_edit_->setValidator(out_w_edit_validator_);

    out_h_edit_validator_ = new QIntValidator(this);
    out_h_edit_validator_->setRange(1, 10000);

    out_h_edit_ = new ALineEdit(this);
    out_h_edit_->setFixedWidth(100);
    out_h_edit_->setValidator(out_h_edit_validator_);

    ALabel *out_size_x_label_ = new ALabel(this);
    out_size_x_label_->setText("x");

    mainLayout->addWidget(out_w_edit_);
    mainLayout->addWidget(out_size_x_label_);
    mainLayout->addWidget(out_h_edit_);
    mainLayout->addSpacing(24);

    out_fps_label_ = new ALabel(this);
    out_fps_combo_ = new AComboBox(this);
    out_fps_combo_->setFixedWidth(70);
    
    mainLayout->addWidget(out_fps_label_);
    mainLayout->addWidget(out_fps_combo_);

    mainLayout->addStretch();

    export_button_ = new APushButton(this);
    export_button_->setFixedHeight(32);
    mainLayout->addWidget(export_button_);
}

void Image2GifSettingView::changeLanguage() {
    out_size_label_->setText("输出大小");
    out_w_edit_->setText("1080");
    out_h_edit_->setText("960");
    out_fps_label_->setText("帧率");
    export_button_->setText("导出");
}

void Image2GifSettingView::sigConnect() {
}
} // namespace image2gif