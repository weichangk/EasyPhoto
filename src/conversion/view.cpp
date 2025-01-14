#include "conversion/view.h"

ConversionView::ConversionView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

void ConversionView::createUi() {
    setObjectName("ConversionView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    QFont iconFont = Font::getIconFont(":/font/iconfont.ttf");

    QWidget *topWidget = new QWidget(this);
    topWidget->setFixedHeight(56);

    m_pAddFileBtn = new VectorButton(topWidget);
    m_pAddFileBtn->setObjectName("VectorButton_HW28_I20");
    m_pAddFileBtn->setFont(iconFont);
    m_pAddFileBtn->setText(QChar(0xe634));

    m_pAddFolderBtn = new VectorButton(topWidget);
    m_pAddFolderBtn->setObjectName("VectorButton_HW28_I20");
    m_pAddFolderBtn->setFont(iconFont);
    m_pAddFolderBtn->setText(QChar(0xe634));

    m_pDelFileBtn = new VectorButton(topWidget);
    m_pDelFileBtn->setObjectName("VectorButton_HW28_I20");
    m_pDelFileBtn->setFont(iconFont);
    m_pDelFileBtn->setText(QChar(0xe634));

    m_pSelectAllCkb = new QCheckBox(topWidget);

    auto topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setContentsMargins(20, 0, 20, 0);
    topWidgetLayout->setSpacing(8);
    topWidgetLayout->addWidget(m_pAddFileBtn, Qt::AlignVCenter);
    topWidgetLayout->addWidget(m_pAddFolderBtn, Qt::AlignVCenter);
    topWidgetLayout->addWidget(m_pDelFileBtn, Qt::AlignVCenter);
    topWidgetLayout->addWidget(m_pSelectAllCkb, Qt::AlignVCenter);
    topWidgetLayout->addStretch();

    QWidget *bottomWidget = new QWidget(this);
    bottomWidget->setFixedHeight(80);

    m_pOutputFormatLbl = new QLabel(bottomWidget);

    m_pOutputFormatCbb = new QComboBox(bottomWidget);
    m_pOutputFormatCbb->setFixedWidth(120);

    m_pOutputFolderLbl = new QLabel(bottomWidget);

    m_pOutputFolderCbb = new QComboBox(bottomWidget);
    m_pOutputFolderCbb->setFixedWidth(120);

    m_pOpenOutputFolderBtn = new VectorButton(bottomWidget);
    m_pOpenOutputFolderBtn->setObjectName("VectorButton_HW28_I20");
    m_pOpenOutputFolderBtn->setFont(iconFont);
    m_pOpenOutputFolderBtn->setText(QChar(0xe634));

    m_pConversionBtn = new QPushButton(bottomWidget);

    auto bottomWidgetLayout = new QHBoxLayout(bottomWidget);
    bottomWidgetLayout->setContentsMargins(20, 0, 20, 0);
    bottomWidgetLayout->setSpacing(0);
    bottomWidgetLayout->addWidget(m_pOutputFormatLbl, Qt::AlignVCenter);
    bottomWidgetLayout->addWidget(m_pOutputFormatCbb, Qt::AlignVCenter);
    bottomWidgetLayout->addWidget(m_pOutputFolderLbl, Qt::AlignVCenter);
    bottomWidgetLayout->addWidget(m_pOutputFolderCbb, Qt::AlignVCenter);
    bottomWidgetLayout->addWidget(m_pOpenOutputFolderBtn, Qt::AlignVCenter);
    bottomWidgetLayout->addStretch();
    bottomWidgetLayout->addWidget(m_pConversionBtn, Qt::AlignVCenter);

    m_pStackedLayout = new QStackedLayout();

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(topWidget);
    layout->addWidget(createDividingLine());
    layout->addLayout(m_pStackedLayout, 1);
    layout->addWidget(createDividingLine());
    layout->addWidget(bottomWidget);
}

void ConversionView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &ConversionView::onLanguageChange);
}

QWidget *ConversionView::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("ConversionView_DividingLine");
    dividingLine->setFixedHeight(1);
    return dividingLine;
}

void ConversionView::onLanguageChange() {
    m_pOutputFormatLbl->setText(tr("Output format:"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pConversionBtn->setText(tr("Conversion"));
}