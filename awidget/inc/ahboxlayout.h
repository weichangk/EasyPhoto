#pragma once
#include "awidget_global.h"
#include <QHBoxLayout>

class AWIDGET_EXPORT AHBoxLayout : public QHBoxLayout
{
    Q_OBJECT
public:
    AHBoxLayout(QWidget *parent = nullptr);
    ~AHBoxLayout();
};
