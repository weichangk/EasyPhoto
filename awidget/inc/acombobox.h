#pragma once
#include "awidget_global.h"
#include <QComboBox>

class AWIDGET_EXPORT AComboBox : public QComboBox
{
    Q_OBJECT
public:
    AComboBox(QWidget *parent = nullptr);
    ~AComboBox();
};
