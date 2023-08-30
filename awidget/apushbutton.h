#pragma once
#include "qpushbutton.h"

class APushButton : public QPushButton
{
    Q_OBJECT
public:
    APushButton(QWidget *parent = nullptr);
    ~APushButton();
};
