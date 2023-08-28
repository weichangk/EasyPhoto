#pragma once
#include "qwidget.h"

class AWidget : public QWidget
{
    Q_OBJECT
public:
    AWidget(QWidget *parent = nullptr);
    ~AWidget();

protected:
    virtual void changeLanguage();
    virtual void sigConnect();
};
