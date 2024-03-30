/*
 * @Author: weick
 * @Date: 2024-03-23 11:24:18
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-30 09:11:38
 */

#include "inc/editsettingview.h"
#include "../awidget/inc/avboxlayout.h"

namespace imageedit {
EditSettingView::EditSettingView(QWidget *parent) {
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
    effect_setting_widget_ = new AWidget(this);
    watermark_setting_widget_ = new AWidget(this);

    tab_widget_->addTab(crop_setting_widget_, "Crop");
    tab_widget_->addTab(effect_setting_widget_, "Effect");
    tab_widget_->addTab(watermark_setting_widget_, "Watermark");
    
    export_button_ = new APushButton(this);
    export_button_->setFixedHeight(32);
    mainLayout->addWidget(tab_widget_, 1);
    mainLayout->addWidget(export_button_);
}

void EditSettingView::changeLanguage() {
    export_button_->setText("Export");
}

void EditSettingView::sigConnect() {
}
} // namespace imageedit