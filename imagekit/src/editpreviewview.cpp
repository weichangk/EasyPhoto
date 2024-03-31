/*
 * @Author: weick
 * @Date: 2024-03-23 11:13:49
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 11:15:27
 */

#include "inc/editpreviewview.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/awidget.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"

namespace imageedit {
EditPreviewView::EditPreviewView(QWidget *parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

EditPreviewView::~EditPreviewView() {
}

void EditPreviewView::createUi() {
    auto mainLayout = new AVBoxLayout(this);
    input_preview_label_ = new ALabel(this);
    input_preview_widget_ = new AWidget(this);
    output_preview_label_ = new ALabel(this);
    output_preview_widget_ = new AWidget(this);
    mainLayout->addWidget(input_preview_label_);
    mainLayout->addWidget(input_preview_widget_, 1);
    mainLayout->addWidget(output_preview_label_);
    mainLayout->addWidget(output_preview_widget_, 1);

    QSizePolicy sizePolicy = this->sizePolicy();
    sizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
    input_preview_label_->setSizePolicy(sizePolicy);
    input_preview_label_->setAlignment(Qt::AlignCenter);
    output_preview_label_->setSizePolicy(sizePolicy);
    output_preview_label_->setAlignment(Qt::AlignCenter);

    // test
    input_preview_widget_->setStyleSheet("background-color: #000000;");
    output_preview_widget_->setStyleSheet("background-color: #000000;");

    input_preview_pixmap_label_ = new ALabel(input_preview_widget_);
    auto input_preview_pixmap_label_layout = new AHBoxLayout();
    input_preview_pixmap_label_layout->addStretch();
    input_preview_pixmap_label_layout->addWidget(input_preview_pixmap_label_);
    input_preview_pixmap_label_layout->addStretch();
    auto input_preview_widget_layout = new AVBoxLayout(input_preview_widget_);
    input_preview_widget_layout->addStretch();
    input_preview_widget_layout->addLayout(input_preview_pixmap_label_layout);
    input_preview_widget_layout->addStretch();

    output_preview_pixmap_label_ = new ALabel(output_preview_widget_);
    auto output_preview_pixmap_label_layout = new AHBoxLayout();
    output_preview_pixmap_label_layout->addStretch();
    output_preview_pixmap_label_layout->addWidget(output_preview_pixmap_label_);
    output_preview_pixmap_label_layout->addStretch();
    auto output_preview_widget_layout = new AVBoxLayout(output_preview_widget_);
    output_preview_widget_layout->addStretch();
    output_preview_widget_layout->addLayout(output_preview_pixmap_label_layout);
    output_preview_widget_layout->addStretch();

    // test
    input_preview_pixmap_label_->setFixedSize(300, 200);
    input_preview_pixmap_label_->setStyleSheet("background-color: red;");
    output_preview_pixmap_label_->setFixedSize(300, 200);
    output_preview_pixmap_label_->setStyleSheet("background-color: blue;");

}

void EditPreviewView::changeLanguage() {
    input_preview_label_->setText(tr("Input"));
    output_preview_label_->setText(tr("Output"));
}

void EditPreviewView::sigConnect() {
}
} // namespace imageedit