/*
 * @Author: weick
 * @Date: 2024-07-02 07:27:00
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-02 08:16:37
 */

#include "inc/apreviewbutton.h"
#include <QEvent>
#include <QMouseEvent>

APreviewButton::APreviewButton(QWidget *parent) :
    AWidget(parent) {
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
}

APreviewButton::~APreviewButton() {
}

QPixmap &APreviewButton::normalIcon() {
    return normal_icon_;
}

void APreviewButton::setNormalIcon(const QPixmap &icon) {
    QImage img1 = icon.toImage();
    QImage img2 = normal_icon_.toImage();
    if (img1 != img2) {
        normal_icon_ = icon;
        emit sigNormalIconChanged(normal_icon_);
        update();
    }
}

QPixmap &APreviewButton::hoverIcon() {
    return hover_icon_;
}

void APreviewButton::setHoverIcon(const QPixmap &icon) {
    QImage img1 = icon.toImage();
    QImage img2 = hover_icon_.toImage();
    if (img1 != img2) {
        hover_icon_ = icon;
        emit sigNormalIconChanged(hover_icon_);
        update();
    }
}

QPixmap &APreviewButton::pressedIcon() {
    return pressed_icon_;
}

void APreviewButton::setPressedIcon(const QPixmap &icon) {
    QImage img1 = icon.toImage();
    QImage img2 = pressed_icon_.toImage();
    if (img1 != img2) {
        pressed_icon_ = icon;
        emit sigNormalIconChanged(pressed_icon_);
        update();
    }
}

bool APreviewButton::eventFilter(QObject *watched, QEvent *event) {
    return AWidget::eventFilter(watched, event);
}

void APreviewButton::paintEvent(QPaintEvent *event) {
}

void APreviewButton::changeEvent(QEvent *event) {
    if (event->type() == QEvent::StyleChange) {
        update();
    }
    AWidget::changeEvent(event);
}

void APreviewButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit sigClicked();
    }
}