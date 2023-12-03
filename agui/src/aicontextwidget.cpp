#include "inc/aicontextwidget.h"
#include "inc/aenum.h"
#include "../acore/inc/astring.h"
#include "../awidget/inc/ahboxlayout.h"
#include <QMetaEnum>

AIconTextWidget::AIconTextWidget(QWidget *parent) : ABaseWidget(parent)
{
    createUi();
}

AIconTextWidget::~AIconTextWidget()
{
}

void AIconTextWidget::setState(AEnum::StyleStatus state)
{
    m_State = state;
    m_Icon->setState(state);
    QString stateStr = AString::QtEnumToQString(state).toLower();
    m_Text->setProperty("style-state", stateStr);
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
    m_Text->setProperty("style-state", "normal");
    m_Text->setStyle(m_Text->style());
    layout->addWidget(m_Icon);
    layout->addSpacing(m_IconTextSpacing);
    layout->addWidget(m_Text);
    layout->addStretch();
}

void AIconTextWidget::mousePressEvent(QMouseEvent *event)
{
    ABaseWidget::mousePressEvent(event);
    m_Icon->setState(AEnum::StyleStatus::Pressed);
    m_Text->setProperty("style-state", "pressed");
    m_Text->setStyle(m_Text->style());
}

void AIconTextWidget::mouseReleaseEvent(QMouseEvent *event)
{
    ABaseWidget::mouseReleaseEvent(event);
    m_Icon->setState(AEnum::StyleStatus::Hover);
    m_Text->setProperty("style-state", "hover");
    m_Text->setStyle(m_Text->style());
}

void AIconTextWidget::enterEvent(QEnterEvent *event)
{
    ABaseWidget::enterEvent(event);
    m_Icon->setState(AEnum::StyleStatus::Hover);
    m_Text->setProperty("style-state", "hover");
    m_Text->setStyle(m_Text->style());
}

void AIconTextWidget::leaveEvent(QEvent *event)
{
    ABaseWidget::leaveEvent(event);
    m_Icon->setState(AEnum::StyleStatus::Normal);
    m_Text->setProperty("style-state", "normal");
    m_Text->setStyle(m_Text->style());
}
