/*
 * @Author: weick
 * @Date: 2023-12-07 23:05:02
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-07 23:28:15
 */

#include "inc/afuncpanelwidget.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include <QMouseEvent>

AFuncPanelWidget::AFuncPanelWidget(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
}

AFuncPanelWidget::~AFuncPanelWidget() {
}

void AFuncPanelWidget::setIcon(QPixmap p) {
    m_Icon->setPixmap(p);
}

void AFuncPanelWidget::createUi() {
    setObjectName("AFuncPanelWidget");
    auto mainLayout = new AHBoxLayout(this);
    mainLayout->setContentsMargins(16, 12, 16, 12);

    auto leftLayout = new AVBoxLayout();
    mainLayout->addLayout(leftLayout, 1);

    m_Name = new ALabel(this);
    m_Name->setObjectName("AFuncPanelWidget_m_Name");

    m_Dec = new ALabel(this);
    m_Dec->setObjectName("AFuncPanelWidget_m_Dec");

    leftLayout->addWidget(m_Name);
    leftLayout->addStretch();
    leftLayout->addWidget(m_Dec);

    m_Icon = new ALabel(this);
    m_Icon->setObjectName("AFuncPanelWidget_m_Icon");
    m_Icon->setFixedSize(40, 40);
    mainLayout->addWidget(m_Icon);
}

void AFuncPanelWidget::mousePressEvent(QMouseEvent *event) {
    ABaseWidget::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        emit sigClicked();
    }
}

void AFuncPanelWidget::resizeEvent(QResizeEvent *event) {
    ABaseWidget::resizeEvent(event);
    m_Icon->setFixedSize(height() - 24, height() - 24);
}
