/*
 * @Author: weick 
 * @Date: 2024-03-29 21:32:06 
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-29 22:28:42
 */

#include "inc/acheckedbutton.h"

ACheckedButton::ACheckedButton(QWidget *parent) :
    APushButton(parent) {
    setIcon(QIcon(":/agui/res/image/unchecked-24.png"));

    sigConnect();
}

ACheckedButton::~ACheckedButton() {
}

void ACheckedButton::setCheck(bool checked) {
    checked_ = checked;
    setIcon(QIcon(checked_ ? ":/agui/res/image/checked-24.png" : ":/agui/res/image/unchecked-24.png"));
}

bool ACheckedButton::isChecked() {
    return checked_;
}

void ACheckedButton::sigConnect() {
    connect(this, &QPushButton::clicked, [=]() {
        setCheck(!checked_);
        emit clicked(checked_);
    });
}