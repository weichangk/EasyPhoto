#include "importguide.h"

ImportGuide::ImportGuide(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

void ImportGuide::createUi() {
    setObjectName("ImportGuide");
    setAttribute(Qt::WA_StyledBackground);
    setFixedSize(470, 193);

    QFont iconFont = Font::getIconFont(":/font/iconfont.ttf");

    m_pImportIconLab = new VectorLabel(this);
    m_pImportIconLab->setObjectName("VectorLabel_Size24");
    m_pImportIconLab->setFont(iconFont);
    m_pImportIconLab->setText(QChar(0xe665));
    m_pImportIconLab->setFixedSize(150, 100);

    m_pImportDecLab = new QLabel(this);

    m_pDividingLine = createDividingLine();
    m_pDividingLine->setVisible(false);

    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->addSpacing(36);
    m_pMainLayout->addWidget(m_pImportIconLab, 0, Qt::AlignHCenter);
    m_pMainLayout->addSpacing(20);
    m_pMainLayout->addWidget(m_pImportDecLab, 0, Qt::AlignHCenter);
    m_pMainLayout->addSpacing(20);
    m_pMainLayout->addWidget(m_pDividingLine, 0, Qt::AlignHCenter);
}

void ImportGuide::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &ImportGuide::onLanguageChange);
}

QWidget *ImportGuide::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("ImportGuide_DividingLine");
    dividingLine->setFixedHeight(1);
    return dividingLine;
}

void ImportGuide::onLanguageChange() {
    m_pImportDecLab->setText(tr("Output format:"));
}