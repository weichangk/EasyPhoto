#include "inc/aicontextwidget.h"
#include "../awidget/inc/ahboxlayout.h"

AIconTextWidget::AIconTextWidget(QWidget *parent) : ABaseWidget(parent)
{
    createUi();
}

AIconTextWidget::~AIconTextWidget()
{
}

void AIconTextWidget::createUi()
{
    setObjectName("AIconTextWidget");
    auto layout = new AHBoxLayout(this);
    m_Icon = new AFourStateImageWidget(this);
    m_Icon->setObjectName("AIconTextWidget_Icon");
    m_Icon->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_Text = new ALabel(this);
    m_Text->setObjectName("AIconTextWidget_Text");
    layout->addWidget(m_Icon);
    layout->addSpacing(m_IconTextSpacing);
    layout->addWidget(m_Text);
    layout->addStretch();
}

void AIconTextWidget::mousePressEvent(QMouseEvent *event)
{
    ABaseWidget::mousePressEvent(event);
    m_Icon->setState(AFourStateImageStatus::Pressed);
}

void AIconTextWidget::mouseReleaseEvent(QMouseEvent *event)
{
    ABaseWidget::mouseReleaseEvent(event);
    m_Icon->setState(AFourStateImageStatus::Hover);
}

void AIconTextWidget::enterEvent(QEnterEvent *event)
{
    ABaseWidget::enterEvent(event);
    m_Icon->setState(AFourStateImageStatus::Hover);
}

void AIconTextWidget::leaveEvent(QEvent *event)
{
    ABaseWidget::leaveEvent(event);
    m_Icon->setState(AFourStateImageStatus::Normal);
}
