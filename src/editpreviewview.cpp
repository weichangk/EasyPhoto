#include "inc/editpreviewview.h"
#include "inc/editcropview.h"
#include "inc/signals.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>

namespace imageedit {
EditPreviewView::EditPreviewView(QWidget *parent) :
    QWidget(parent){
    createUi();
    sigConnect();
}

EditPreviewView::~EditPreviewView() {
}

void EditPreviewView::createUi() {
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    input_preview_label_ = new QLabel(this);
    input_preview_widget_ = new QWidget(this);
    output_preview_label_ = new QLabel(this);
    output_preview_widget_ = new QWidget(this);

    input_preview_label_->setText(tr("Input"));
    output_preview_label_->setText(tr("Output"));

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

    input_preview_pixmap_label_ = new QLabel(input_preview_widget_);
    auto input_preview_pixmap_label_layout = new QHBoxLayout();
    input_preview_pixmap_label_layout->setContentsMargins(0, 0, 0, 0);
    input_preview_pixmap_label_layout->addStretch();
    input_preview_pixmap_label_layout->addWidget(input_preview_pixmap_label_);
    input_preview_pixmap_label_layout->addStretch();
    auto input_preview_widget_layout = new QVBoxLayout(input_preview_widget_);
    input_preview_widget_layout->setContentsMargins(0, 0, 0, 0);
    input_preview_widget_layout->addStretch();
    input_preview_widget_layout->addLayout(input_preview_pixmap_label_layout);
    input_preview_widget_layout->addStretch();

    output_preview_pixmap_label_ = new QLabel(output_preview_widget_);
    auto output_preview_pixmap_label_layout = new QHBoxLayout();
    output_preview_pixmap_label_layout->setContentsMargins(0, 0, 0, 0);
    output_preview_pixmap_label_layout->addStretch();
    output_preview_pixmap_label_layout->addWidget(output_preview_pixmap_label_);
    output_preview_pixmap_label_layout->addStretch();
    auto output_preview_widget_layout = new QVBoxLayout(output_preview_widget_);
    output_preview_widget_layout->setContentsMargins(0, 0, 0, 0);
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

void EditPreviewView::sigConnect() {
    connect(SIGNALS, &Signals::sigWindowMove, this, &EditPreviewView::updateCropViewGeometry);
    connect(SIGNALS, &Signals::sigListItemDataSelected, this, &EditPreviewView::preViewDataSelected);
    connect(crop_view_, &EditCropView::sigSelectRectChangedEnd, this, &EditPreviewView::selectRectChangedEnd);
    connect(crop_view_, &EditCropView::sigSelectRectChanged, this, &EditPreviewView::selectRectChanged);
    connect(SIGNALS, &Signals::sigSelectRectSetting2Preview, this, &EditPreviewView::setCropViewSelectionRect);
    connect(SIGNALS, &Signals::sigEqualRatioCropSetting2Preview, this, &EditPreviewView::cropUseAspectRatio);

    connect(SIGNALS, &Signals::sigRotateAngleSetting2Preview, this, &EditPreviewView::rotateAngleChanged);

    connect(SIGNALS, &Signals::sigLuminanceSetting2Preview, this, &EditPreviewView::luminanceChanged);
    connect(SIGNALS, &Signals::sigContrastSetting2Preview, this, &EditPreviewView::contrastChanged);
    connect(SIGNALS, &Signals::sigSaturationSetting2Preview, this, &EditPreviewView::saturationChanged);
    connect(SIGNALS, &Signals::sigEffectResetSetting2Preview, this, &EditPreviewView::effectReset);
}

void EditPreviewView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    updateCropViewGeometry();
    crop_view_->show();
}

void EditPreviewView::hideEvent(QHideEvent *event) {
    QWidget::hideEvent(event);
    crop_view_->hide();
}

void EditPreviewView::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    updateInputPixmapSize();
    QTimer::singleShot(100, [=]() {
        updateCropViewGeometry();
    }); 
}

void EditPreviewView::moveEvent(QMoveEvent *event) {
    QWidget::moveEvent(event);
    updateCropViewGeometry();
}

void EditPreviewView::preViewDataSelected(Data *data) {
    data_ = data;
    loadInputPixmap(data->file_path);
    updateInputPixmapSize();
    // 等待updateInputPixmapSize()布局刷新input_preview_pixmap_label_->setFixedSize获取正确坐标
    QTimer::singleShot(100, [=]() {
        updateCropViewGeometry();
    });
}

void EditPreviewView::updateCropViewGeometry() {
    if(!data_) {
        return;
    }

    if(data_->preview_ratio == 0) {
        data_->preview_ratio = static_cast<qreal>(data_->crop_rect.width()) / input_preview_pixmap_label_->width();
        crop_view_->setAspectRatio(data_->aspect_ratio);
    }

    setCropViewSelectionRect(data_->crop_rect);
    emit SIGNALS->sigSelectRectPreview2Setting(data_->crop_rect);
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

void EditPreviewView::selectRectChanged(const QRect &rect) {
    QRect r = PreviewRect2CropRect(rect, data_->preview_ratio);
    emit SIGNALS->sigSelectRectPreview2Setting(r);
}

void EditPreviewView::selectRectChangedEnd(const QRect &rect) {
    QRect r = PreviewRect2CropRect(rect, data_->preview_ratio);
    data_->crop_rect = r;
}

void EditPreviewView::setCropViewSelectionRect(const QRect &rect) {
    QRect r = CropRect2PreviewRect(rect, data_->preview_ratio);
    crop_view_->setSelectionRect(r);
}

void EditPreviewView::cropUseAspectRatio(bool use) {
    crop_view_->setUseAspectRatio(use);
}

void EditPreviewView::rotateAngleChanged(int angle) {
}

void EditPreviewView::luminanceChanged(int value) {
}
void EditPreviewView::contrastChanged(int value) {
}
void EditPreviewView::saturationChanged(int value) {
}
void EditPreviewView::effectReset(int luminance, int contrast, int saturation) {
}
} // namespace imageedit