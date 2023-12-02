#include "inc/apushbutton.h"
#include <QEvent>
#include <QCoreApplication>

APushButton::APushButton(QWidget *parent) : QPushButton(parent)
{
    installEventFilter(this);
}

APushButton::~APushButton()
{
}

void APushButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
}
