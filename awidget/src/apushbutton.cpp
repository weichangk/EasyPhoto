/*
 * @Author: weick
 * @Date: 2023-12-05 22:59:28
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 22:59:28
 */

#include "inc/apushbutton.h"
#include <QEvent>
#include <QCoreApplication>

APushButton::APushButton(QWidget *parent) :
    QPushButton(parent) {
    installEventFilter(this);
}

APushButton::~APushButton() {
}

void APushButton::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event);
}
