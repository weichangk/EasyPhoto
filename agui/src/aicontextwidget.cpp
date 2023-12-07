/*
 * @Author: weick
 * @Date: 2023-12-05 22:55:08
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-07 23:25:49
 */

#include "inc/aicontextwidget.h"
#include "inc/aenum.h"
#include "../acore/inc/astring.h"
#include "../awidget/inc/ahboxlayout.h"
#include <QMetaEnum>
#include <QMouseEvent>

AIconTextWidget::AIconTextWidget(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
}

AIconTextWidget::~AIconTextWidget() {
}

void AIconTextWidget::setState(AEnum::StyleStatus state) {
    m_State = state;
    m_Icon->setState(state);
    QString stateStr = AString::QtEnumToQString(state).toLower();
    m_Text->setProperty("style-state", stateStr);
    m_Text->setStyle(m_Text->style());
}

void AIconTextWidget::createUi() {
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

void AIconTextWidget::mousePressEvent(QMouseEvent *event) {
    ABaseWidget::mousePressEvent(event);
    if (m_State != AEnum::StyleStatus::Checked) {
        m_Icon->setState(AEnum::StyleStatus::Pressed);
        m_Text->setProperty("style-state", "pressed");
        m_Text->setStyle(m_Text->style());
    }
    if (event->button() == Qt::LeftButton)
    {
        emit sigClicked();
    }
}

void AIconTextWidget::mouseReleaseEvent(QMouseEvent *event) {
    ABaseWidget::mouseReleaseEvent(event);
    if (m_State != AEnum::StyleStatus::Checked) {
        m_Icon->setState(AEnum::StyleStatus::Hover);
        m_Text->setProperty("style-state", "hover");
        m_Text->setStyle(m_Text->style());
    }
}

void AIconTextWidget::enterEvent(QEnterEvent *event) {
    ABaseWidget::enterEvent(event);
    if (m_State != AEnum::StyleStatus::Checked) {
        m_Icon->setState(AEnum::StyleStatus::Hover);
        m_Text->setProperty("style-state", "hover");
        m_Text->setStyle(m_Text->style());
    }
}

void AIconTextWidget::leaveEvent(QEvent *event) {
    ABaseWidget::leaveEvent(event);
    if (m_State != AEnum::StyleStatus::Checked) {
        m_Icon->setState(AEnum::StyleStatus::Normal);
        m_Text->setProperty("style-state", "normal");
        m_Text->setStyle(m_Text->style());
    }
}

void AIconTextWidget::changeEvent(QEvent *event) {
    ABaseWidget::changeEvent(event);
    if (event->type() == QEvent::EnabledChange) {
        if (!isEnabled()) {
            m_State = AEnum::StyleStatus::Disabled;
            m_Icon->setState(AEnum::StyleStatus::Disabled);
            m_Text->setProperty("style-state", "disabled");
            m_Text->setStyle(m_Text->style());
        }
    }
}
