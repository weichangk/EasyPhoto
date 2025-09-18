#include "upsc/modelcard.h"
#include "filter/maskwidget.h"

ModelCard:: ModelCard(QWidget *parent) :
    QWidget(parent) {
    setObjectName("UpscModelCard");
    setAttribute(Qt::WA_StyledBackground);

    m_pNameLbl = new QLabel(this);
    m_pNameLbl->setObjectName("UpscModelCard_m_pNameLbl");
    m_pNameLbl->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_pNameLbl->setVisible(false);

    m_pDescLbl = new QLabel(this);
    m_pDescLbl->setObjectName("UpscModelCard_m_pDescLbl");
    m_pDescLbl->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    // m_pDescLbl->setWordWrap(true); // 会影响主窗体最大化！

    m_pThumbFrame = new QWidget(this);
    m_pThumbFrame->setObjectName("UpscModelCard_m_pThumbFrame");
    m_pThumbFrame->setFixedHeight(112);

    auto thumbFrameLayout = new QHBoxLayout(m_pThumbFrame);
    thumbFrameLayout->setContentsMargins(0, 0, 0, 0);
    thumbFrameLayout->setSpacing(0);

    m_pBeforeThumbLbl = new QLabel(m_pThumbFrame);
    m_pBeforeThumbLbl->setObjectName("UpscModelCard_m_pBeforeThumbLbl");
    m_pBeforeThumbLbl->setFixedSize(112, 112);

    m_pAfterThumbLbl = new QLabel(m_pThumbFrame);
    m_pAfterThumbLbl->setObjectName("UpscModelCard_m_pAfterThumbLbl");
    m_pAfterThumbLbl->setFixedSize(112, 112);

    thumbFrameLayout->addStretch();
    thumbFrameLayout->addWidget(m_pBeforeThumbLbl);
    thumbFrameLayout->addSpacing(1);
    thumbFrameLayout->addWidget(m_pAfterThumbLbl);
    thumbFrameLayout->addStretch();

    m_pBeforeLbl = new QLabel(m_pBeforeThumbLbl);
    m_pBeforeLbl->setObjectName("UpscModelCard_m_pBeforeLbl");
    m_pBeforeLbl->setAlignment(Qt::AlignCenter);
    m_pBeforeLbl->adjustSize();

    m_pAfterLbl = new QLabel(m_pAfterThumbLbl);
    m_pAfterLbl->setObjectName("UpscModelCard_m_pAfterLbl");
    m_pAfterLbl->setAlignment(Qt::AlignCenter);
    m_pAfterLbl->adjustSize();

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_pNameLbl);
    mainLayout->addWidget(m_pDescLbl);
    mainLayout->addSpacing(8);
    mainLayout->addWidget(m_pThumbFrame);

    auto mask = new QtmFilter::MaskWidget(m_pThumbFrame);
    mask->setPramas(QtmFilter::MaskWidget::RoundType::Round_All, 0, 8, 8);
}

void ModelCard::setInfo(const QString &title, const QString &desc, const QPixmap &beforeThumb, const QPixmap &afterThumb) {
    m_pNameLbl->setText(title);
    m_pDescLbl->setText(desc);
    m_pBeforeThumbLbl->setPixmap(beforeThumb.scaled(m_pBeforeThumbLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pAfterThumbLbl->setPixmap(afterThumb.scaled(m_pAfterThumbLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pBeforeLbl->setText(tr("Before"));
    m_pAfterLbl->setText(tr("After"));

    QFont font = m_pBeforeLbl->font();
    QFontMetricsF metrics(font);
    int bWidth = metrics.horizontalAdvance(m_pBeforeLbl->text()) + 8;
    int aWidth = metrics.horizontalAdvance(m_pAfterLbl->text()) + 8;
    m_pBeforeLbl->setGeometry(10, m_pBeforeThumbLbl->height() - m_pBeforeLbl->height() - 4, bWidth, m_pBeforeLbl->height());
    m_pAfterLbl->setGeometry(m_pAfterThumbLbl->width() - aWidth - 10, m_pAfterThumbLbl->height() - m_pAfterLbl->height() - 4, aWidth, m_pAfterLbl->height());
}

void ModelCard::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
}