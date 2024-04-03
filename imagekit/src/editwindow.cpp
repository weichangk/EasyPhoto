/*
 * @Author: weick
 * @Date: 2024-03-23 11:01:48
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-29 22:17:22
 */

#include "inc/editwindow.h"
#include "inc/signals.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ashadoweffect.h"
#include <QPainter>
#include <QPainterPath>

namespace imageedit {
EditWindow::EditWindow(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

EditWindow::~EditWindow() {
}

void EditWindow::changeFileListData(QList<Data> datas) {
    file_list_view_->changeData(datas);
}

void EditWindow::createUi() {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(1200, 760);

    auto mainLayout = new AVBoxLayout(this);

    topbar_ = new ATopbar(this);
    topbar_->setCloseBtnTopRight10Radius();
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
    name_label_->setText("图片编辑");
    logoLayout->addWidget(name_label_);
    topbarLayout->addLayout(logoLayout);
    topbarLayout->addStretch();

    auto bodyLayout = new AHBoxLayout();
    bodyLayout->setContentsMargins(25, 0, 25, 25);

    auto bodyBg = new AWidget(this);
    bodyBg->setObjectName("edit_window_body_bg");
    bodyLayout->addWidget(bodyBg);
    auto bodyBgLayout = new AHBoxLayout(bodyBg);

    file_list_view_ = new EditFileListView(this);
    file_list_view_->setFixedWidth(260);
    bodyBgLayout->addWidget(file_list_view_);

    preview_view_ = new EditPreviewView(this);
    bodyBgLayout->addWidget(preview_view_, 1);

    setting_view_ = new EditSettingView(this);
    setting_view_->setFixedWidth(300);
    bodyBgLayout->addWidget(setting_view_);

    mainLayout->addLayout(bodyLayout, 1);

    auto shadow = new AShadowEffect(this);
}

void EditWindow::changeLanguage() {
}

void EditWindow::sigConnect() {
    connect(topbar_, &ATopbar::sigMin, this, [=]() { showMinimized(); });
    connect(topbar_, &ATopbar::sigMax, this, [=]() { showMaximized(); });
    connect(topbar_, &ATopbar::sigNormal, this, [=]() { showNormal(); });
    connect(topbar_, &ATopbar::sigClose, this, [=]() {
        close();
        emit ::Signals::getInstance()->sigGotoFunc(ImageFunc::STARTUP);
    });
}
void EditWindow::paintEvent(QPaintEvent *event) {
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

void EditWindow::moveEvent(QMoveEvent *event) {
    ABaseWidget::moveEvent(event);
    emit Signals::getInstance()->sigWindowMove();
}
} // namespace imageedit