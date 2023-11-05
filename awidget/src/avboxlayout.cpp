#include "inc/avboxlayout.h"

AVBoxLayout::AVBoxLayout(QWidget *parent) : QVBoxLayout(parent)
{
    setSpacing(0);
    setContentsMargins(0, 0, 0, 0);
}

AVBoxLayout::~AVBoxLayout()
{
}
