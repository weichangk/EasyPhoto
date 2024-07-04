/*
 * @Author: weick
 * @Date: 2024-07-02 07:27:00
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-02 08:16:37
 */

#include "inc/apreviewbutton.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>

inline QRect previewButtonRect(QRect btnRect, QSize iconSize) {
    auto rc = btnRect.adjusted(1, 1, -1, -1);
    return QRect(rc.x() + (rc.width() - iconSize.width())  / 2, rc.y() + (rc.height() - iconSize.height())  / 2, iconSize.width(), iconSize.height());
}

APreviewButton::APreviewButton(QWidget *parent) :
    AWidget(parent),
    icon_state_(kNormal) {
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

APreviewButton::~APreviewButton() {
}

QPixmap &APreviewButton::normalIcon() {
    return normal_icon_;
}

void APreviewButton::setNormalIcon(const QPixmap &icon) {
    icon_state_ = kNormal;
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
    icon_state_ = kHover;
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
    icon_state_ = kPressed;
    QImage img1 = icon.toImage();
    QImage img2 = pressed_icon_.toImage();
    if (img1 != img2) {
        pressed_icon_ = icon;
        emit sigNormalIconChanged(pressed_icon_);
        update();
    }
}

QSize &APreviewButton::iconSize() {
    return icon_size_;
}

void APreviewButton::setIconSize(const QSize &size) {
    if (icon_size_ != size) {
        icon_size_ = size;
        emit sigIconSizeChanged(icon_size_);
        update();
    }
}

bool APreviewButton::eventFilter(QObject *watched, QEvent *event) {
    return AWidget::eventFilter(watched, event);
}

void APreviewButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap iconPixmap;
    switch (icon_state_) {
        case kNormal:
            iconPixmap = normal_icon_;
            break;
        case kHover:
            iconPixmap = hover_icon_;
            break;
        case kPressed:
            iconPixmap = pressed_icon_;
            break;
        default:
            iconPixmap = normal_icon_;
            break;
    }
    auto iconRc = previewButtonRect(this->rect(), icon_size_);
    painter.drawPixmap(iconRc, iconPixmap);
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