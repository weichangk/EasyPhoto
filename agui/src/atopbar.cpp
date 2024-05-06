/*
 * @Author: weick
 * @Date: 2023-12-05 22:55:51
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-14 23:30:12
 */

#include "inc/atopbar.h"
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/ahboxlayout.h"
#include <QMouseEvent>
#include <QFile>

ATopbar::ATopbar(QWidget *parent) :
    ACanMoveWidget(parent) {
    createUi();
    changeLanguage();
    sigConnect();
}

ATopbar::~ATopbar() {
}

QWidget *ATopbar::contentWidget() {
    return m_contentWidget;
}

void ATopbar::setNormalVisible(bool visible) {
#ifdef Q_OS_MAC
#else
    m_maxBtn->setVisible(!visible);
    m_normalBtn->setVisible(visible);
#endif
}

void ATopbar::setCloseBtnTopRight10Radius() {
    m_closeBtn->setObjectName("ATopbar_m_closeBtn_10Radius");
    m_closeBtn->setStyle(m_closeBtn->style());
}

void ATopbar::setMinVisible(bool visible) {
    m_minBtn->setVisible(visible);
    m_minMacBtn->setVisible(visible);
}

void ATopbar::setMaxVisible(bool visible) {
    m_maxBtn->setVisible(visible);
    m_maxMacBtn->setVisible(visible);
}
void ATopbar::setCloseVisible(bool visible) {
    m_closeBtn->setVisible(visible);
    m_closeMacBtn->setVisible(visible);
}

void ATopbar::createUi() {
    setFixedHeight(40); // 36

    m_minMacBtn = new APushButton(this);
    m_minMacBtn->setObjectName("ATopbar_m_minMacBtn");
    m_minMacBtn->setFixedSize(40, 40);
    m_maxMacBtn = new APushButton(this);
    m_maxMacBtn->setObjectName("ATopbar_m_maxMacBtn");
    m_maxMacBtn->setFixedSize(40, 40);
    m_normalMacBtn = new APushButton(this);
    m_normalMacBtn->setObjectName("ATopbar_m_normalMacBtn");
    m_normalMacBtn->setFixedSize(40, 40);
    m_closeMacBtn = new APushButton(this);
    m_closeMacBtn->setObjectName("ATopbar_m_closeMacBtn");
    m_closeMacBtn->setFixedSize(40, 40);

    m_contentWidget = new QWidget(this);
    m_contentWidget->setAttribute(Qt::WA_TranslucentBackground);

    m_minBtn = new APushButton(this);
    m_minBtn->setObjectName("ATopbar_m_minBtn");
    m_minBtn->setFixedSize(40, 40);
    m_maxBtn = new APushButton(this);
    m_maxBtn->setObjectName("ATopbar_m_maxBtn");
    m_maxBtn->setFixedSize(40, 40);
    m_normalBtn = new APushButton(this);
    m_normalBtn->setObjectName("ATopbar_m_normalBtn");
    m_normalBtn->setFixedSize(40, 40);
    m_closeBtn = new APushButton(this);
    m_closeBtn->setObjectName("ATopbar_m_closeBtn");
    m_closeBtn->setFixedSize(40, 40);

    auto lyt = new AHBoxLayout(this);
    lyt->setContentsMargins(0, 0, 0, 0);
    lyt->setSpacing(0);
    lyt->addWidget(m_minMacBtn);
    lyt->addWidget(m_maxMacBtn);
    lyt->addWidget(m_normalMacBtn);
    lyt->addWidget(m_closeMacBtn);
    lyt->addWidget(m_contentWidget, 1);
    lyt->addWidget(m_minBtn);
    lyt->addWidget(m_maxBtn);
    lyt->addWidget(m_normalBtn);
    lyt->addWidget(m_closeBtn);

//
#ifdef Q_OS_MAC
    m_minMacBtn->setVisible(true);
    m_maxMacBtn->setVisible(true);
    m_normalMacBtn->setVisible(true);
    m_closeMacBtn->setVisible(true);
    m_minBtn->setVisible(false);
    m_maxBtn->setVisible(false);
    m_normalBtn->setVisible(false);
    m_closeBtn->setVisible(false);
#else
    m_minMacBtn->setVisible(false);
    m_maxMacBtn->setVisible(false);
    m_normalMacBtn->setVisible(false);
    m_closeMacBtn->setVisible(false);
    m_minBtn->setVisible(true);
    setNormalVisible(false);
    m_closeBtn->setVisible(true);
#endif
}
void ATopbar::changeLanguage() {
    m_minBtn->setToolTip(tr("Minimize"));
    m_maxBtn->setToolTip(tr("Maximize"));
    m_normalBtn->setToolTip(tr("Normal"));
    m_closeBtn->setToolTip(tr("Close"));
}

void ATopbar::sigConnect() {
    connect(m_minBtn, &QPushButton::clicked, this, &ATopbar::sigMin);
    connect(m_closeBtn, &QPushButton::clicked, this, &ATopbar::sigClose);
    connect(m_maxBtn, &QPushButton::clicked, this, [=]() {
        emit sigMax();
        setNormalVisible(true);
    });
    connect(m_normalBtn, &QPushButton::clicked, this, [=]() {
        emit sigNormal();
        setNormalVisible(false);
    });
}
