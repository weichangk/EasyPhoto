/*
 * @Author: weick
 * @Date: 2024-04-12 07:42:18
 * @Last Modified by: weick
 * @Last Modified time: 2024-04-12 07:51:00
 */

#include "inc/aimportguide.h"
#include "../awidget/inc/avboxlayout.h"

AImportGuide::AImportGuide(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

AImportGuide::~AImportGuide() {
}

void AImportGuide::createUi() {
    import_btn_ = new APushButton(this);
    import_btn_->setFixedSize(200, 200);

    auto mainLayout = new AVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(import_btn_);
    mainLayout->addStretch();
}

void AImportGuide::changeLanguage() {
}

void AImportGuide::sigConnect() {
    connect(import_btn_, &APushButton::clicked, this, &AImportGuide::sigClicked);
}