/*
 * @Author: weick
 * @Date: 2024-03-23 11:01:48
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-06 16:37:59
 */

#include "inc/image2gifwindow.h"
#include "inc/signals.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ashadoweffect.h"
#include <QPainter>
#include <QPainterPath>

namespace image2gif {
Image2GifWindow::Image2GifWindow(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

Image2GifWindow::~Image2GifWindow() {
}

void Image2GifWindow::changeFileListData(QList<Data> datas) {
    if (datas.count() == 0) {
        stacked_widget_->setCurrentIndex(0);
    } else {
        stacked_widget_->setCurrentIndex(1);
    }
    file_list_view_->changeData(datas);
}

void Image2GifWindow::setFileListCurrentIndex(int index) {
    file_list_view_->setCurrentIndex(index);
}

int Image2GifWindow::fileListCurrentIndex() {
    return file_list_view_->currentIndex();
}

void Image2GifWindow::createUi() {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(1200, 760);

    auto mainLayout = new AVBoxLayout(this);

    topbar_ = new ATopbar(this);
    topbar_->setCloseBtnTopRight10Radius();
    topbar_->setMinVisible(false);
    topbar_->setMaxVisible(false);
    mainLayout->addWidget(topbar_);

    auto topbarLayout = new AHBoxLayout(topbar_->contentWidget());
    topbarLayout->setSpacing(12);
    topbarLayout->addSpacing(12);
    auto logoLayout = new AHBoxLayout();
    logoLayout->setSpacing(4);
    logo_label_ = new ALabel(this);
    QPixmap logo(":/agui/res/image/Compression-logo-32.png");
    logo_label_->setPixmap(logo);
    logoLayout->addWidget(logo_label_);
    name_label_ = new ALabel(this);
    name_label_->setObjectName("edit_window_name_lable");
    name_label_->setText("生成GIF");
    logoLayout->addWidget(name_label_);
    topbarLayout->addLayout(logoLayout);
    topbarLayout->addStretch();

    auto bodyLayout = new AHBoxLayout();
    bodyLayout->setContentsMargins(25, 0, 25, 25);

    auto bodyBg = new AWidget(this);
    bodyBg->setObjectName("edit_window_body_bg");
    bodyLayout->addWidget(bodyBg, 1);
    auto bodyBgLayout = new AHBoxLayout(bodyBg);
    
    stacked_widget_ = new AStackedWidget(this);
    bodyBgLayout->addWidget(stacked_widget_, 1);

    import_guide_ = new AImportGuide(this);
    stacked_widget_->addWidget(import_guide_);

    auto viewsWidget = new AWidget(this);
    stacked_widget_->addWidget(viewsWidget);

    auto viewsWidgetLayout = new AHBoxLayout(viewsWidget);

    file_list_view_ = new Image2GifFileListView(this);
    file_list_view_->setFixedWidth(400);
    viewsWidgetLayout->addWidget(file_list_view_);

    auto viewsWidgetRightLayout = new AVBoxLayout();
    viewsWidgetLayout->addLayout(viewsWidgetRightLayout, 1);

    preview_view_ = new Image2GifPreviewView(this);
    viewsWidgetRightLayout->addWidget(preview_view_, 1);

    setting_view_ = new Image2GifSettingView(this);
    setting_view_->setFixedHeight(70);
    viewsWidgetRightLayout->addWidget(setting_view_);

    mainLayout->addLayout(bodyLayout, 1);

    generating_widget_ = new AWidgetWithRotatingItem(QPixmap(":agui/res/image/loading-96.png"), preview_view_);
    generating_widget_->setFixedSize(96, 96);
    generating_widget_->setVisible(false);

    auto shadow = new AShadowEffect(this);
}

void Image2GifWindow::changeLanguage() {
}

void Image2GifWindow::sigConnect() {
    connect(topbar_, &ATopbar::sigMin, this, [=]() { showMinimized(); });
    connect(topbar_, &ATopbar::sigMax, this, [=]() { showMaximized(); });
    connect(topbar_, &ATopbar::sigNormal, this, [=]() { showNormal(); });
    connect(topbar_, &ATopbar::sigClose, this, [=]() {
        close();
        emit ::Signals::getInstance()->sigGotoFunc(ImageFunc::STARTUP);
    });
    connect(import_guide_, &AImportGuide::sigClicked, this, [=]() {
        emit Signals::getInstance()->sigOpenFileDialog(this);
    });
}
void Image2GifWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 背景色透明
    painter.fillRect(this->rect(), QColor(0, 0, 0, 1));

    // 背景图
    QPixmap pixmapTemp = QPixmap(this->rect().size());
    pixmapTemp.fill(QColor("#181818"));
    pixmapTemp.setDevicePixelRatio(1);

    // 背景图圆角裁剪
    QPainterPath path;
    path.addRoundedRect(this->rect(), 10, 10);
    painter.setClipPath(path);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(this->rect(), pixmapTemp);

    // 边框
    QPen pen(QColor("#402F38"));
    pen.setWidth(1);
    painter.setPen(pen);
    auto borderRect = this->rect(); //.adjusted(1, 1, -1, -1);
    painter.drawRoundedRect(borderRect, 10, 10);
}

void Image2GifWindow::moveEvent(QMoveEvent *event) {
    ABaseWidget::moveEvent(event);
    emit Signals::getInstance()->sigWindowMove();
}

void Image2GifWindow::resizeEvent(QResizeEvent *event) {
    ABaseWidget::resizeEvent(event);
    generating_widget_->setGeometry((preview_view_->width() - generating_widget_->width()) / 2,
                                    (preview_view_->height() - generating_widget_->height()) / 2,
                                    generating_widget_->width(),
                                    generating_widget_->height());
}

void Image2GifWindow::generatingWidgetVisible(bool visible) {
    generating_widget_->setVisible(visible);
    if (visible) {
        generating_widget_->start();
    } else {
        generating_widget_->stop();
    }
}
} // namespace image2gif