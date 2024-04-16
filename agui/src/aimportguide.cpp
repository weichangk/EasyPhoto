/*
 * @Author: weick
 * @Date: 2024-04-12 07:42:18
 * @Last Modified by: weick
 * @Last Modified time: 2024-04-16 08:02:55
 */

#include "inc/aimportguide.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"

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

    auto btn_layout = new AVBoxLayout();
    btn_layout->addStretch();
    btn_layout->addWidget(import_btn_);
    btn_layout->addStretch();

    auto mainLayout = new AHBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(btn_layout);
    mainLayout->addStretch();
}

void AImportGuide::changeLanguage() {
}

void AImportGuide::sigConnect() {
    connect(import_btn_, &APushButton::clicked, this, &AImportGuide::sigClicked);
}