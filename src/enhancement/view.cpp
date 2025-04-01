#include "enhancement/view.h"

#include <QCoreApplication>

EnhancementView::EnhancementView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

void EnhancementView::createUi() {
    setObjectName("EnhancementView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setObjectName("EnhancementView_m_pTitleLbl");
    auto titleLabLayout = new QHBoxLayout();
    titleLabLayout->setContentsMargins(20, 0, 0, 0);
    titleLabLayout->addWidget(m_pTitleLbl, 0, Qt::AlignLeft);

    m_pBodyWidget = new QWidget(this);
    auto bodyWidgetLayout = new QHBoxLayout(m_pBodyWidget);
    bodyWidgetLayout->setContentsMargins(0, 0, 0, 0);
    bodyWidgetLayout->setSpacing(0);

    m_pLeftWidget = new QWidget(this);
    auto LeftWidgetLayout = new QHBoxLayout(m_pLeftWidget);
    LeftWidgetLayout->setContentsMargins(0, 0, 0, 0);
    LeftWidgetLayout->setSpacing(0);

    m_pRightWidget = new QWidget(this);
    m_pRightWidget->setFixedWidth(320);
    m_pRightWidget->setStyleSheet("background-color: blue;");

    bodyWidgetLayout->addWidget(m_pLeftWidget, 1);
    bodyWidgetLayout->addWidget(m_pRightWidget);

    m_pLeftWidgetStackedLayout = new QStackedLayout();

    m_pImportGuideWidget = new QWidget(this);
    QVBoxLayout *importGuideLayout = new QVBoxLayout(m_pImportGuideWidget);
    importGuideLayout->setContentsMargins(20, 20, 20, 20);
    importGuideLayout->setSpacing(0);

    m_pImportGuide = new ImportGuide(this);

    m_pSmapleWidget = new QWidget(this);
    m_pSmapleWidget->setFixedHeight(100);
    auto smapleWidgetLayout = new QVBoxLayout(m_pSmapleWidget);
    smapleWidgetLayout->setContentsMargins(0, 0, 0, 0);
    smapleWidgetLayout->setSpacing(0);

    m_pSmapleTitleLbl = new QLabel(this);
    m_pSmapleTitleLbl->setAlignment(Qt::AlignCenter);

    m_pSmaple1ImageLbl = new QLabel(this);
    m_pSmaple1ImageLbl->setFixedSize(128, 72);
    m_pSmaple2ImageLbl = new QLabel(this);
    m_pSmaple2ImageLbl->setFixedSize(128, 72);

    auto sampleImageLayout = new QHBoxLayout();
    sampleImageLayout->setContentsMargins(0, 0, 0, 0);
    sampleImageLayout->setSpacing(14);
    sampleImageLayout->addStretch();
    sampleImageLayout->addWidget(m_pSmaple1ImageLbl);
    sampleImageLayout->addWidget(m_pSmaple2ImageLbl);
    sampleImageLayout->addStretch();

    smapleWidgetLayout->addWidget(m_pSmapleTitleLbl);
    smapleWidgetLayout->addLayout(sampleImageLayout);

    importGuideLayout->addWidget(m_pImportGuide, 1);
    importGuideLayout->addSpacing(14);
    importGuideLayout->addWidget(m_pSmapleWidget);
    
    m_pLeftWidgetStackedLayout->addWidget(m_pImportGuideWidget);

    auto leftWidgetStackedMarginLayout = new QVBoxLayout();
    leftWidgetStackedMarginLayout->setContentsMargins(0, 0, 0, 0);
    leftWidgetStackedMarginLayout->addLayout(m_pLeftWidgetStackedLayout, 1);

    LeftWidgetLayout->addLayout(leftWidgetStackedMarginLayout, 1);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(titleLabLayout, 0);
    layout->addWidget(m_pBodyWidget, 1);

    loadSampleImage();
}

void EnhancementView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &EnhancementView::onLanguageChange);
}

void EnhancementView::loadSampleImage() {
    QString execDir = QCoreApplication::applicationDirPath();
    m_pSmaple1ImageLbl->setPixmap(QPixmap(QString("%1/sample1.webp").arg(execDir)).scaled(m_pSmaple1ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pSmaple2ImageLbl->setPixmap(QPixmap(QString("%1/sample2.webp").arg(execDir)).scaled(m_pSmaple2ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void EnhancementView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Ai Image Enhancer"));
    m_pSmapleTitleLbl->setText(tr("Try with one of our smaples!"));
}