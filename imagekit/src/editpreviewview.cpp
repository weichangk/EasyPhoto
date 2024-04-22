/*
 * @Author: weick
 * @Date: 2024-03-23 11:13:49
 * @Last Modified by: weick
 * @Last Modified time: 2024-04-02 07:51:19
 */

#include "inc/editpreviewview.h"
#include "inc/editcropview.h"
#include "inc/signals.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/awidget.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"
#include <QTimer>

namespace imageedit {
EditPreviewView::EditPreviewView(QWidget *parent) :
    ABaseWidget(parent) {
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
    // input_preview_widget_->setStyleSheet("background-color: #000000;");
    // output_preview_widget_->setStyleSheet("background-color: #000000;");

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
    input_preview_widget_->setStyleSheet("background-color: green;");
    output_preview_widget_->setStyleSheet("background-color: yellow;");
    input_preview_pixmap_label_->setFixedSize(300, 200);
    input_preview_pixmap_label_->setStyleSheet("background-color: red;");
    output_preview_pixmap_label_->setFixedSize(300, 200);
    output_preview_pixmap_label_->setStyleSheet("background-color: blue;");

    crop_view_ = new EditCropView(this);
    
}

void EditPreviewView::changeLanguage() {
    input_preview_label_->setText(tr("Input"));
    output_preview_label_->setText(tr("Output"));
}

void EditPreviewView::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigWindowMove, this, &EditPreviewView::updateCropViewGeometry);
    connect(Signals::getInstance(), &Signals::sigFileListItemSelected, this, &EditPreviewView::preViewDataSelected);
    connect(crop_view_, &EditCropView::sigSelectRectChangedEnd, this, &EditPreviewView::selectRectChangedEnd);
    connect(crop_view_, &EditCropView::sigSelectRectChanged, this, [=](const QRect &rect) {
        emit Signals::getInstance()->sigSelectRectChanged(rect);
    });
}

void EditPreviewView::showEvent(QShowEvent *event) {
    ABaseWidget::showEvent(event);
    updateCropViewGeometry();
    crop_view_->show();
}

void EditPreviewView::hideEvent(QHideEvent *event) {
    ABaseWidget::hideEvent(event);
    crop_view_->hide();
}

void EditPreviewView::resizeEvent(QResizeEvent *event) {
    ABaseWidget::resizeEvent(event);
    updateInputPixmapSize();
    QTimer::singleShot(100, [=]() {
        updateCropViewGeometry();
    }); 
}

void EditPreviewView::moveEvent(QMoveEvent *event) {
    ABaseWidget::moveEvent(event);
    updateCropViewGeometry();
}

void EditPreviewView::preViewDataSelected(Data data) {
    data_ = data;
    loadInputPixmap(data.file_path);
    updateInputPixmapSize();
    // 等待updateInputPixmapSize()布局刷新input_preview_pixmap_label_->setFixedSize获取正确坐标
    QTimer::singleShot(100, [=]() {
        updateCropViewGeometry();
    });
}

void EditPreviewView::updateCropViewGeometry() {
    QRect selectionRect = data_.crop_rect;
    if(selectionRect.isEmpty()) {
        selectionRect = QRect(0, 0, input_preview_pixmap_label_->width(), input_preview_pixmap_label_->height());
    }
    crop_view_->setSelectionRect(selectionRect);
    emit Signals::getInstance()->sigSelectRectChanged(selectionRect);
    QPoint globalPos = input_preview_pixmap_label_->mapToGlobal(QPoint(0, 0));
    crop_view_->setGeometry(globalPos.x(), globalPos.y(), input_preview_pixmap_label_->width(), input_preview_pixmap_label_->height());
}

void EditPreviewView::loadInputPixmap(const QString &path) {
    input_pixmap_ = QPixmap(path);
}

void EditPreviewView::updateInputPixmapSize() {
    if(input_pixmap_.isNull()) {
        return;
    }

    // 计算缩放比例，确保图片适应窗口大小
    qreal widthRatio = static_cast<qreal>(input_preview_widget_->width()) / input_pixmap_.width();
    qreal heightRatio = static_cast<qreal>(input_preview_widget_->height()) / input_pixmap_.height();
    qreal scaleRatio = qMin(widthRatio, heightRatio);

    // 缩放图片
    QPixmap pixmap = input_pixmap_.scaled(input_pixmap_.size() * scaleRatio,
                                                 Qt::KeepAspectRatio,
                                                 Qt::SmoothTransformation);
                                                 qDebug() << "pixmap size:" << pixmap.size();

    input_preview_pixmap_label_->setFixedSize(pixmap.size());
    input_preview_pixmap_label_->setPixmap(pixmap);

    output_preview_pixmap_label_->setFixedSize(pixmap.size());
    output_preview_pixmap_label_->setPixmap(pixmap);
}

void EditPreviewView::selectRectChangedEnd(const QRect &rect) {
    data_.crop_rect = rect;
    emit Signals::getInstance()->sigDataUpdate(data_);
}

} // namespace imageedit