/*
 * @Author: weick
 * @Date: 2023-12-07 23:05:02
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-08 23:31:44
 */

#include "inc/afuncpanelwidget.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include <QMouseEvent>

AFuncPanelWidget::AFuncPanelWidget(QWidget *parent, int id) :
    ABaseWidget(parent),
    m_Id(id) {
    createUi();
}

AFuncPanelWidget::~AFuncPanelWidget() {
}

void AFuncPanelWidget::createUi() {
    setObjectName("AFuncPanelWidget");
    auto mainLayout = new AHBoxLayout(this);

    auto leftLayout = new AVBoxLayout();
    mainLayout->addLayout(leftLayout);

    m_Name = new ALabel(this);
    m_Name->setObjectName("AFuncPanelWidget_m_Name");

    m_Dec = new ALabel(this);
    m_Dec->setObjectName("AFuncPanelWidget_m_Dec");

    leftLayout->addWidget(m_Name);
    leftLayout->addStretch();
    leftLayout->addWidget(m_Dec);

    m_Icon = new ALabel(this);
    m_Icon->setObjectName("AFuncPanelWidget_m_Icon");
    mainLayout->addStretch();
    mainLayout->addWidget(m_Icon);
}

void AFuncPanelWidget::mousePressEvent(QMouseEvent *event) {
    ABaseWidget::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        emit sigClicked(m_Id);
    }
}

void AFuncPanelWidget::resizeEvent(QResizeEvent *event) {
    ABaseWidget::resizeEvent(event);
    int left, top, right, bottom;
    layout()->getContentsMargins(&left, &top, &right, &bottom);
    m_Icon->setFixedSize(height() - top - bottom, height() - top - bottom);
}
