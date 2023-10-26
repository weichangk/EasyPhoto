#pragma once
#include "awidget_global.h"
#include <QVBoxLayout>

class AWIDGET_EXPORT AVBoxLayout : public QVBoxLayout
{
    Q_OBJECT
public:
    AVBoxLayout(QWidget *parent = nullptr);
    ~AVBoxLayout();
};
