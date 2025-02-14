#include "gifgeneration/view.h"
#include "gifgeneration/presenter.h"
// #include "gifgeneration/compressiontask.h"
#include "settings.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>

GifGenerationView::GifGenerationView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

void GifGenerationView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    listViewNoDataState();
}

void GifGenerationView::createUi() {
    setObjectName("GifGenerationView");
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

    m_pListModeSwitchBtn = new VectorButton(topWidget);
    m_pListModeSwitchBtn->setObjectName("VectorButton_HW28_I20");
    m_pListModeSwitchBtn->setFont(iconFont);
    m_pListModeSwitchBtn->setText(QChar(0xe634));

    auto topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setContentsMargins(20, 0, 20, 0);
    topWidgetLayout->setSpacing(8);
    topWidgetLayout->addWidget(m_pAddFileBtn);
    topWidgetLayout->addWidget(m_pAddFolderBtn);
    topWidgetLayout->addWidget(m_pClearFileBtn);
    topWidgetLayout->addStretch();
    topWidgetLayout->addWidget(m_pListModeSwitchBtn);

    QWidget *bottomWidget = new QWidget(this);
    bottomWidget->setFixedHeight(80);

    m_pOutputFolderLbl = new QLabel(bottomWidget);

    m_pOutputFolderCbb = new QComboBox(bottomWidget);
    m_pOutputFolderCbb->setFixedWidth(120);

    m_pOutputFolderCbbFilter = new ComboBoxFilter(m_pOutputFolderCbb);
    m_pOutputFolderCbb->installEventFilter(m_pOutputFolderCbbFilter);

    initOutputFolderCbbItem();

    m_pOpenOutputFolderBtn = new VectorButton(bottomWidget);
    m_pOpenOutputFolderBtn->setObjectName("VectorButton_HW28_I20");
    m_pOpenOutputFolderBtn->setFont(iconFont);
    m_pOpenOutputFolderBtn->setText(QChar(0xe634));

    m_pPreviewBtn = new QPushButton(bottomWidget);
    m_pGenerationBtn = new QPushButton(bottomWidget);

    auto bottomWidgetLayout = new QHBoxLayout(bottomWidget);
    bottomWidgetLayout->setContentsMargins(20, 0, 20, 0);
    bottomWidgetLayout->setSpacing(0);
    bottomWidgetLayout->addWidget(m_pOutputFolderLbl);
    bottomWidgetLayout->addWidget(m_pOutputFolderCbb);
    bottomWidgetLayout->addWidget(m_pOpenOutputFolderBtn);
    bottomWidgetLayout->addStretch();
    bottomWidgetLayout->addWidget(m_pPreviewBtn);
    bottomWidgetLayout->addWidget(m_pGenerationBtn);

    m_pImportGuide = new ImportGuide(this);
    m_pImportGuideWidget = new QWidget(this);
    QVBoxLayout *importGuideLayout = new QVBoxLayout(m_pImportGuideWidget);
    importGuideLayout->setAlignment(Qt::AlignCenter);
    importGuideLayout->addWidget(m_pImportGuide);

    m_pListView = new ListView<SGifGenerationData>(this);
    m_pListView->setSpacing(0);
    m_pListDelegate = new GifGenerationListDelegate(m_pListView);
    m_pListView->setItemDelegate(m_pListDelegate);
    m_pListView->viewport()->installEventFilter(m_pListDelegate);

    m_pStackedLayout = new QStackedLayout();
    m_pStackedLayout->addWidget(m_pImportGuideWidget);
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

void GifGenerationView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &GifGenerationView::onLanguageChange);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &GifGenerationView::listViewImportFile);
    connect(m_pAddFileBtn, &QPushButton::clicked, this, &GifGenerationView::onAddFileBtnClicked);
    connect(m_pAddFolderBtn, &QPushButton::clicked, this, &GifGenerationView::onAddFolderBtnClicked);
    connect(m_pClearFileBtn, &QPushButton::clicked, this, &GifGenerationView::onClearFileBtnClicked);
    connect(m_pListModeSwitchBtn, &QPushButton::clicked, this, &GifGenerationView::onListModeSwitchBtnClicked);
    connect(m_pListView, &QListView::clicked, this, &GifGenerationView::onListViewClicked);
    connect(m_pOutputFolderCbbFilter, &ComboBoxFilter::sigClicked, this, &GifGenerationView::onOutputFolderCbbClicked);
    connect(m_pOutputFolderCbb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &GifGenerationView::onOutputFolderCbbIndexChanged);
    connect(m_pOpenOutputFolderBtn, &QPushButton::clicked, this, &GifGenerationView::onOpenOutputFolderBtnClicked);
    connect(m_pPreviewBtn, &QPushButton::clicked, this, &GifGenerationView::onPreviewBtnClicked);
    connect(m_pGenerationBtn, &QPushButton::clicked, this, &GifGenerationView::onGenerationBtnClicked);
}

QWidget *GifGenerationView::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("GifGenerationView_DividingLine");
    dividingLine->setFixedHeight(1);
    return dividingLine;
}

void GifGenerationView::listViewImportFile(const QStringList &filePaths) {
    GifGenerationPresenter *prst = dynamic_cast<GifGenerationPresenter *>(presenter());
    prst->appendData(filePaths);
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
}

void GifGenerationView::onListModeSwitchBtnClicked() {
    GifGenerationPresenter *prst = dynamic_cast<GifGenerationPresenter *>(presenter());
    if (!prst->datas().isEmpty()) {
        m_pListDelegate->setListMode(!m_pListDelegate->isListMode());
        m_pListModeSwitchBtn->setText(m_pListDelegate->isListMode() ? QChar(0xe634) : QChar(0xe634));
        m_pListView->changeData(prst->datas());
    }
}

void GifGenerationView::listItemDelete(const QString &filePath) {
    GifGenerationPresenter *prst = dynamic_cast<GifGenerationPresenter *>(presenter());
    QStringList filePaths;
    filePaths.append(filePath);
    prst->deleteData(filePaths);
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
};

void GifGenerationView::listViewNoDataState() {
    GifGenerationPresenter *prst = dynamic_cast<GifGenerationPresenter *>(presenter());
    bool isNoData = prst->datas().isEmpty();
    m_pClearFileBtn->setVisible(!isNoData);
    m_pListModeSwitchBtn->setVisible(!isNoData);
    m_pStackedLayout->setCurrentWidget(isNoData ? m_pImportGuideWidget : m_pListView);
}

void GifGenerationView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->compressionOutPath());
    m_pOutputFolderCbb->addItem("...");
}

void GifGenerationView::GifGenerationView::setOutputFolder(const QString &path) {
    SETTINGS->setCompressionOutPath(path);
    m_pOutputFolderCbb->setItemText(0, path);
}

void GifGenerationView::onLanguageChange() {
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pPreviewBtn->setText(tr("Preview"));
    m_pGenerationBtn->setText(tr("Generation"));
}

void GifGenerationView::onAddFileBtnClicked() {
    QString title = tr("Open");
    QString directory = SETTINGS->compressionLastAddFilePath();
    QStringList filePaths = QFileDialog::getOpenFileNames(this, title, directory, "All Files (*)");
    if (!filePaths.isEmpty()) {
        QFileInfo fileInfo(filePaths.first());
        QString lastDirectory = fileInfo.absolutePath();
        SETTINGS->setCompressionLastAddFilePath(lastDirectory);
        listViewImportFile(filePaths);
    }
}

void GifGenerationView::onAddFolderBtnClicked() {
    QString title = tr("Select Folder");
    QString folderPath = QFileDialog::getExistingDirectory(this, title, SETTINGS->compressionLastAddFolderPath());
    if (!folderPath.isEmpty()) {
        SETTINGS->setCompressionLastAddFolderPath(folderPath);
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

void GifGenerationView::onClearFileBtnClicked() {
    GifGenerationPresenter *prst = dynamic_cast<GifGenerationPresenter *>(presenter());
    prst->clearData();
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
}

void GifGenerationView::onListViewClicked(const QModelIndex &index) {
    auto data = index.data(Qt::UserRole).value<SGifGenerationData>();
    QRect rc = m_pListView->visualRect(index);
    int posx = m_pListView->mapFromGlobal(QCursor::pos()).x();
    int posy = m_pListView->mapFromGlobal(QCursor::pos()).y();
    auto bgRect = rc.adjusted(0, 0, -8, -8);
    auto delRect = QRect(bgRect.right() - 4 - 16, bgRect.y() + 4, 16, 16);
    if (posx >= delRect.x() && posx <= delRect.x() + delRect.width()
        && posy >= delRect.y() && posy <= delRect.y() + delRect.height()) {
        listItemDelete(data.file_path);
    }
}

void GifGenerationView::onOutputFolderCbbClicked() {
}

void GifGenerationView::onOutputFolderCbbIndexChanged(int index) {
    if (index == 1) {
        blockSignalsFunc(m_pOutputFolderCbb, [&]() {
            m_pOutputFolderCbb->setCurrentIndex(0);
        });
        QString title = tr("Select Folder");
        QString dirPath = QFileDialog::getExistingDirectory(this, title, QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (!dirPath.isEmpty()) {
            setOutputFolder(dirPath);
        }
    }
}

void GifGenerationView::onOpenOutputFolderBtnClicked() {
    QString folderPath = SETTINGS->compressionOutPath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
}

void GifGenerationView::onPreviewBtnClicked() {
}

void GifGenerationView::onGenerationBtnClicked() {
}