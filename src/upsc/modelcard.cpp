#include "upsc/modelcard.h"

ModelCard::ModelCard(QWidget *parent) :
    QWidget(parent) {
    setObjectName("ModelCard");
    setAttribute(Qt::WA_StyledBackground);

    m_pNameLbl = new QLabel(this);
    m_pNameLbl->setObjectName("ModelCard_m_pNameLbl");
    m_pNameLbl->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    m_pDescLbl = new QLabel(this);
    m_pDescLbl->setObjectName("ModelCard_m_pDescLbl");
    m_pDescLbl->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_pDescLbl->setWordWrap(true);

    m_pThumbFrame = new QWidget(this);
    m_pThumbFrame->setObjectName("ModelCard_m_pThumbFrame");
    m_pThumbFrame->setFixedHeight(200);

    auto thumbFrameLayout = new QHBoxLayout(m_pThumbFrame);
    thumbFrameLayout->setContentsMargins(0, 0, 0, 0);
    thumbFrameLayout->setSpacing(0);

    m_pBeforeThumbLbl = new QLabel(m_pThumbFrame);
    m_pBeforeThumbLbl->setObjectName("ModelCard_m_pBeforeThumbLbl");
    m_pBeforeThumbLbl->setFixedSize(200, 200);

    m_pAfterThumbLbl = new QLabel(m_pThumbFrame);
    m_pAfterThumbLbl->setObjectName("ModelCard_m_pAfterThumbLbl");
    m_pAfterThumbLbl->setFixedSize(200, 200);

    thumbFrameLayout->addWidget(m_pBeforeThumbLbl);
    thumbFrameLayout->addSpacing(1);
    thumbFrameLayout->addWidget(m_pAfterThumbLbl);

    m_pBeforeLbl = new QLabel(m_pBeforeThumbLbl);
    m_pBeforeLbl->setObjectName("ModelCard_m_pBeforeLbl");

    m_pAfterLbl = new QLabel(m_pAfterThumbLbl);
    m_pAfterLbl->setObjectName("ModelCard_m_pAfterLbl");

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_pNameLbl);
    mainLayout->addWidget(m_pDescLbl, 1);
    mainLayout->addWidget(m_pThumbFrame);
}

void ModelCard::setInfo(const QString &name, const QString &desc, const QPixmap &beforeThumb, const QPixmap &afterThumb) {
    m_pNameLbl->setText(name);
    m_pDescLbl->setText(desc);
    m_pBeforeThumbLbl->setPixmap(beforeThumb.scaled(m_pBeforeThumbLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pAfterThumbLbl->setPixmap(afterThumb.scaled(m_pAfterThumbLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pBeforeLbl->setText(tr("Before"));
    m_pAfterLbl->setText(tr("After"));

    m_pBeforeLbl->setGeometry(10, m_pBeforeThumbLbl->height() - m_pBeforeLbl->height() - 4, m_pBeforeLbl->width(), m_pBeforeLbl->height());
    m_pAfterLbl->setGeometry(m_pAfterThumbLbl->width() - m_pAfterLbl->width() - 0, m_pAfterThumbLbl->height() - m_pAfterLbl->height() - 4, m_pAfterLbl->width(), m_pAfterLbl->height());
}

void ModelCard::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
}