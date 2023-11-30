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
    auto layout = new AHBoxLayout(this);
    m_Icon = new AFourStateImageWidget(this);
    m_Text = new ALabel(this);
    layout->addSpacing(m_IconLeftSpacing);
    layout->addWidget(m_Icon);
    layout->addSpacing(m_IconRightSpacing);
    layout->addWidget(m_Text);
    layout->addStretch();
}
