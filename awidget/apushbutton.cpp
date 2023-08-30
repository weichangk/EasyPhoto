#include "apushbutton.h"

APushButton::APushButton(QWidget *parent) : QPushButton(parent)
{
    setAttribute(Qt::WA_StyledBackground);
}

APushButton::~APushButton()
{
}
