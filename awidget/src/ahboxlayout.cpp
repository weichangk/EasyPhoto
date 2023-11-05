#include "inc/ahboxlayout.h"

AHBoxLayout::AHBoxLayout(QWidget *parent) : QHBoxLayout(parent)
{
    setSpacing(0);
    setContentsMargins(0, 0, 0, 0);
}

AHBoxLayout::~AHBoxLayout()
{
}
