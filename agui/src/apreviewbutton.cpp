/*
 * @Author: weick
 * @Date: 2024-07-02 07:27:00
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-02 08:16:37
 */

#include "inc/apreviewbutton.h"

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
    // if (icon != normal_icon_) {
    //     normal_icon_ = icon;
    //     emit sigNormalIconChanged();
    //     update();
    // }
}

QPixmap &APreviewButton::hoverIcon() {
    return hover_icon_;
}

void APreviewButton::setHoverIcon(const QPixmap &icon) {

}

QPixmap &APreviewButton::pressedIcon() {
    return pressed_icon_;
}

void APreviewButton::setPressedIcon(const QPixmap &icon) {
}

bool APreviewButton::eventFilter(QObject *watched, QEvent *event) {
    return AWidget::eventFilter(watched, event);
}

void APreviewButton::paintEvent(QPaintEvent *event) {
}