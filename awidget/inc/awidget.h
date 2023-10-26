#pragma once
#include "awidget_global.h"

class AWIDGET_EXPORT AWidget : public QWidget
{
    Q_OBJECT
public:
    AWidget(QWidget *parent = nullptr);
    ~AWidget();
};
