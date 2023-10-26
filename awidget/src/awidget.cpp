#include "inc/awidget.h"
#include <QEvent>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>

AWidget::AWidget(QWidget *parent) : QWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);
    setAttribute(Qt::WA_StyledBackground);
}

AWidget::~AWidget()
{
}
