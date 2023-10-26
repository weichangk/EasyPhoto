#pragma once
#include "awidget_global.h"
#include <QPushButton>

class AWIDGET_EXPORT APushButton : public QPushButton
{
    Q_OBJECT
public:
    APushButton(QWidget *parent = nullptr);
    ~APushButton();

protected:
    void paintEvent(QPaintEvent *event) override;
    virtual void showEvent(QShowEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void enterEvent(QEnterEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);

private:
};
