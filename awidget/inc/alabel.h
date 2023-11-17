#pragma once
#include "awidget_global.h"
#include <QLabel>

class AWIDGET_EXPORT ALabel : public QLabel
{
public:
    ALabel(QWidget *parent = nullptr);
    ~ALabel();
};
