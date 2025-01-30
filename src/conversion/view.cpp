#include "conversion/view.h"
#include "conversion/presenter.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>

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

    m_pClearFileBtn = new VectorButton(topWidget);
    m_pClearFileBtn->setObjectName("VectorButton_HW28_I20");
    m_pClearFileBtn->setFont(iconFont);
    m_pClearFileBtn->setText(QChar(0xe634));

    m_pSelectAllCkb = new QCheckBox(topWidget);

    m_pListModeSwitchBtn = new VectorButton(topWidget);
    m_pListModeSwitchBtn->setObjectName("VectorButton_HW28_I20");
    m_pListModeSwitchBtn->setFont(iconFont);
    m_pListModeSwitchBtn->setText(QChar(0xe634));

    auto topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setContentsMargins(20, 0, 20, 0);
    topWidgetLayout->setSpacing(8);
    topWidgetLayout->addWidget(m_pAddFileBtn, Qt::AlignVCenter);
    topWidgetLayout->addWidget(m_pAddFolderBtn, Qt::AlignVCenter);
    topWidgetLayout->addWidget(m_pClearFileBtn, Qt::AlignVCenter);
    topWidgetLayout->addWidget(m_pSelectAllCkb, Qt::AlignVCenter);
    topWidgetLayout->addStretch();
    topWidgetLayout->addWidget(m_pListModeSwitchBtn, Qt::AlignVCenter);

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

    m_pImportGuide = new ImportGuide(this);
    QWidget *importGuideWidget = new QWidget(this);
    QVBoxLayout *importGuideLayout = new QVBoxLayout(importGuideWidget);
    importGuideLayout->setAlignment(Qt::AlignCenter);
    importGuideLayout->addWidget(m_pImportGuide);

    m_pListView = new ListView<Data>(this);
    m_pListView->setSpacing(0);
    m_pListDelegate = new ListDelegate(m_pListView);
    m_pListView->setItemDelegate(m_pListDelegate);
    m_pListView->viewport()->installEventFilter(m_pListDelegate);

    m_pStackedLayout = new QStackedLayout();
    m_pStackedLayout->addWidget(importGuideWidget);
    m_pStackedLayout->addWidget(m_pListView);
    auto stackedMarginLayout = new QVBoxLayout();
    stackedMarginLayout->setContentsMargins(8, 8, 2, 8);
    stackedMarginLayout->addLayout(m_pStackedLayout, 1);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(topWidget);
    layout->addWidget(createDividingLine());
    layout->addLayout(stackedMarginLayout, 1);
    layout->addWidget(createDividingLine());
    layout->addWidget(bottomWidget);
}

void ConversionView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &ConversionView::onLanguageChange);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &ConversionView::listViewImportFile);
    connect(m_pAddFileBtn, &QPushButton::clicked, this, &ConversionView::onAddFileBtnClicked);
    connect(m_pAddFolderBtn, &QPushButton::clicked, this, &ConversionView::onAddFolderBtnClicked);
    connect(m_pClearFileBtn, &QPushButton::clicked, this, &ConversionView::onClearFileBtnClicked);
    connect(m_pSelectAllCkb, &QCheckBox::stateChanged, this, &ConversionView::onSelectAllStateChanged);
    connect(m_pListModeSwitchBtn, &QPushButton::clicked, this, &ConversionView::listModeSwitch);
}

QWidget *ConversionView::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("ConversionView_DividingLine");
    dividingLine->setFixedHeight(1);
    return dividingLine;
}

void ConversionView::listViewImportFile(const QStringList filePaths) {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    prst->appendData(filePaths);
    if(!prst->datas().isEmpty()) {
        m_pListView->changeData(prst->datas());
        m_pStackedLayout->setCurrentWidget(m_pListView);
    }
}

void ConversionView::listModeSwitch() {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    if(!prst->datas().isEmpty()) {
        m_pListDelegate->setListMode(!m_pListDelegate->isListMode());
        m_pListModeSwitchBtn->setText(m_pListDelegate->isListMode() ? QChar(0xe634) : QChar(0xe634));
        m_pListView->changeData(prst->datas());
        m_pListView->update();
    }
}

void ConversionView::onLanguageChange() {
    m_pSelectAllCkb->setText(tr("Select All"));
    m_pOutputFormatLbl->setText(tr("Output format:"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pConversionBtn->setText(tr("Conversion"));
}

void ConversionView::onAddFileBtnClicked() {
    QString title = tr("Open");
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QStringList filePaths = QFileDialog::getOpenFileNames(this, title, directory, "All Files (*)");
    if (!filePaths.isEmpty()) {
        listViewImportFile(filePaths);
    }
}

void ConversionView::onAddFolderBtnClicked() {
    QString title = tr("Select Folder");
    QString folderPath = QFileDialog::getExistingDirectory(nullptr, title, QDir::homePath());
    if (!folderPath.isEmpty()) {
        QDir dir(folderPath);
        QStringList files = dir.entryList(QDir::Files);
        QStringList filePaths;
        for (const QString &file : files) {
            QString filePath = dir.absoluteFilePath(file);
            filePaths.append(filePath);
        }
        if (!filePaths.isEmpty()) {
            listViewImportFile(filePaths);
        }
    }
}

void ConversionView::onClearFileBtnClicked() {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    prst->clearData();
    m_pListView->changeData(prst->datas());
    m_pListView->update();
}

void ConversionView::onSelectAllStateChanged(int state) {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    prst->checkedAllData(state);
    m_pListView->changeData(prst->datas());
    m_pListView->update();
}