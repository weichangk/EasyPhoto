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

void APushButton::showEvent(QShowEvent *event)
{
    QPushButton::showEvent(event);
}

void APushButton::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);
}

void APushButton::enterEvent(QEnterEvent *event)
{
    QPushButton::enterEvent(event);
}

bool APushButton::eventFilter(QObject *watched, QEvent *event)
{
    return QPushButton::eventFilter(watched, event);
}
