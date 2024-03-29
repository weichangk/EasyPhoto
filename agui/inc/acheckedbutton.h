/*
 * @Author: weick
 * @Date: 2024-03-29 21:13:37
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-29 21:32:41
 */

#pragma once
#include "agui_global.h"
#include "../awidget/inc/apushbutton.h"

class AGUI_EXPORT ACheckedButton : public APushButton {
    Q_OBJECT
public:
    ACheckedButton(QWidget *parent = nullptr);
    ~ACheckedButton();
    void setCheck(bool checked);
    bool isChecked();

Q_SIGNALS:
    void clicked(bool isClicked);

private:
    void sigConnect();

private:
    bool checked_ = false;
};