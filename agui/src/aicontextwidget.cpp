#include "inc/aicontextwidget.h"
#include "inc/astylestatus.h"
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

void AIconTextWidget::setState(StyleStatus state)
{
    m_State = state;
    m_Icon->setState(state);
    QString stateStr = QString(QMetaEnum::fromType<StyleStatus>().valueToKey(state)).toLower();
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
    m_Icon->setState(StyleStatus::Pressed);
    // QString stateStr = QString(QMetaEnum::fromType<StyleStatus>().valueToKey(StyleStatus::Pressed)).toLower();
    // m_Text->setProperty("style-state", stateStr);
    m_Text->setStyle(m_Text->style());
}

void AIconTextWidget::mouseReleaseEvent(QMouseEvent *event)
{
    ABaseWidget::mouseReleaseEvent(event);
    m_Icon->setState(StyleStatus::Hover);
    // QString stateStr = QString(QMetaEnum::fromType<StyleStatus>().valueToKey(StyleStatus::Hover)).toLower();
    // m_Text->setProperty("style-state", stateStr);
    m_Text->setStyle(m_Text->style());
}

void AIconTextWidget::enterEvent(QEnterEvent *event)
{
    ABaseWidget::enterEvent(event);
    m_Icon->setState(StyleStatus::Hover);
    // QString stateStr = QString(QMetaEnum::fromType<StyleStatus>().valueToKey(StyleStatus::Hover)).toLower();
    // m_Text->setProperty("style-state", stateStr);
    m_Text->setStyle(m_Text->style());
}

void AIconTextWidget::leaveEvent(QEvent *event)
{
    ABaseWidget::leaveEvent(event);
    m_Icon->setState(StyleStatus::Normal);
    // QString stateStr = QString(QMetaEnum::fromType<StyleStatus>().valueToKey(StyleStatus::Normal)).toLower();
    // m_Text->setProperty("style-state", stateStr);
    m_Text->setStyle(m_Text->style());
}
