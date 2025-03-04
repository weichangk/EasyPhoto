#include "gifgeneration/view.h"
#include "gifgeneration/presenter.h"
#include "gifgeneration/gifgenerationtask.h"
#include "settings.h"

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

    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setObjectName("GifGenerationView_m_pTitleLbl");
    auto titleLabLayout = new QHBoxLayout();
    titleLabLayout->setContentsMargins(20, 0, 0, 0);
    titleLabLayout->addWidget(m_pTitleLbl, 0, Qt::AlignLeft);

    //
    m_pImportGuide = new ImportGuide(this);
    m_pImportGuideWidget = new QWidget(this);
    QVBoxLayout *importGuideLayout = new QVBoxLayout(m_pImportGuideWidget);
    importGuideLayout->setContentsMargins(20, 20, 20, 20);
    importGuideLayout->setSpacing(0);
    importGuideLayout->addWidget(m_pImportGuide);

    //
    QWidget *topWidget = new QWidget(this);
    topWidget->setFixedHeight(56);

    m_pAddFileBtn = new IconButton(topWidget);
    m_pAddFileBtn->setFixedSize(32, 32);
    m_pAddFileBtn->setIconSize(32, 32);
    m_pAddFileBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/old/icon/icon_state/icon32/icon32_add_file.png");

    m_pAddFolderBtn = new IconButton(topWidget);
    m_pAddFolderBtn->setFixedSize(32, 32);
    m_pAddFolderBtn->setIconSize(32, 32);
    m_pAddFolderBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/old/icon/icon_state/icon32/icon32_add_folder.png");

    m_pClearFileBtn = new IconButton(topWidget);
    m_pClearFileBtn->setFixedSize(24, 24);
    m_pClearFileBtn->setIconSize(24, 24);
    m_pClearFileBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/old/icon/icon_state/icon24/icon24_delete.png");

    m_pListModeSwitchBtn = new IconButton(topWidget);
    m_pListModeSwitchBtn->setFixedSize(24, 24);
    m_pListModeSwitchBtn->setIconSize(24, 24);
    m_pListModeSwitchBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/old/icon/icon_state/icon24/icon24_thumbnail.png");

    auto topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setContentsMargins(20, 0, 20, 0);
    topWidgetLayout->setSpacing(12);
    topWidgetLayout->addWidget(m_pAddFileBtn);
    topWidgetLayout->addWidget(m_pAddFolderBtn);
    topWidgetLayout->addStretch();
    topWidgetLayout->addWidget(m_pClearFileBtn);
    topWidgetLayout->addWidget(m_pListModeSwitchBtn);

    QWidget *bottomWidget = new QWidget(this);
    bottomWidget->setFixedHeight(70);

    m_pOutputFolderLbl = new QLabel(bottomWidget);
    m_pOutputFolderLbl->setObjectName("GifGenerationView_m_pOutputFolderLbl");

    m_pOutputFolderCbb = new QComboBox(bottomWidget);
    m_pOutputFolderCbb->setFixedSize(240, 24);

    m_pOutputFolderCbbFilter = new ComboBoxFilter(m_pOutputFolderCbb);
    m_pOutputFolderCbb->installEventFilter(m_pOutputFolderCbbFilter);

    initOutputFolderCbbItem();

    m_pOpenOutputFolderBtn = new IconButton(bottomWidget);
    m_pOpenOutputFolderBtn->setFixedSize(24, 24);
    m_pOpenOutputFolderBtn->setIconSize(24, 24);
    m_pOpenOutputFolderBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/old/icon/icon_state/icon24/icon24_file.png");

    m_pPixelsLbl = new QLabel(bottomWidget);
    m_pPixelsLbl->setObjectName("GifGenerationView_m_pPixelsLbl");
    m_pPixels_x_Lbl = new QLabel(bottomWidget);
    m_pPixels_x_Lbl->setObjectName("GifGenerationView_m_pPixels_x_Lbl");

    m_pPixelsWidthLdt = new QLineEdit(bottomWidget);
    m_pPixelsWidthLdt->setFixedSize(48, 24);
    m_pPixelsHeightLdt = new QLineEdit(bottomWidget);
    m_pPixelsHeightLdt->setFixedSize(48, 24);

    m_pFrameRateLbl = new QLabel(bottomWidget);
    m_pFrameRateLbl->setObjectName("GifGenerationView_m_pFrameRateLbl");
    m_pFrameRateCbb = new QComboBox(bottomWidget);
    initFrameRateCbbItem();

    m_pPreviewBtn = new QPushButton(bottomWidget);
    m_pPreviewBtn->setObjectName("GifGenerationView_m_pPreviewBtn");
    m_pPreviewBtn->setFixedSize(110, 32);

    m_pStartAllBtn = new QPushButton(bottomWidget);
    m_pStartAllBtn->setObjectName("GifGenerationView_m_pStartAllBtn");
    m_pStartAllBtn->setFixedSize(110, 32);

    auto bottomWidgetLayout = new QHBoxLayout(bottomWidget);
    bottomWidgetLayout->setContentsMargins(20, 0, 20, 0);
    bottomWidgetLayout->setSpacing(0);
    bottomWidgetLayout->addWidget(m_pOutputFolderLbl);
    bottomWidgetLayout->addWidget(m_pOutputFolderCbb);
    bottomWidgetLayout->addWidget(m_pOpenOutputFolderBtn);
    bottomWidgetLayout->addWidget(m_pPixelsLbl);
    bottomWidgetLayout->addWidget(m_pPixelsWidthLdt);
    bottomWidgetLayout->addWidget(m_pPixels_x_Lbl);
    bottomWidgetLayout->addWidget(m_pPixelsHeightLdt);
    bottomWidgetLayout->addWidget(m_pFrameRateLbl);
    bottomWidgetLayout->addWidget(m_pFrameRateCbb);
    bottomWidgetLayout->addStretch();
    bottomWidgetLayout->addWidget(m_pPreviewBtn);
    bottomWidgetLayout->addWidget(m_pStartAllBtn);

    m_pListView = new ListView<SGifGenerationData>(this);
    m_pListView->setSpacing(0);
    m_pListDelegate = new GifGenerationListDelegate(m_pListView);
    m_pListView->setItemDelegate(m_pListDelegate);
    m_pListView->viewport()->installEventFilter(m_pListDelegate);
    auto listViewLayout = new QVBoxLayout();
    listViewLayout->setContentsMargins(20, 0, 2, 0);
    listViewLayout->setSpacing(0);
    listViewLayout->addWidget(m_pListView, 1);

    m_pContentWidget = new QWidget(this);
    auto contentWidgetLayout = new QVBoxLayout(m_pContentWidget);
    contentWidgetLayout->setContentsMargins(0, 0, 0, 0);
    contentWidgetLayout->setSpacing(0);
    contentWidgetLayout->addWidget(topWidget);
    contentWidgetLayout->addLayout(listViewLayout, 1);
    contentWidgetLayout->addWidget(createDividingLine());
    contentWidgetLayout->addWidget(bottomWidget);

    m_pStackedLayout = new QStackedLayout();
    m_pStackedLayout->addWidget(m_pImportGuideWidget);
    m_pStackedLayout->addWidget(m_pContentWidget);

    auto stackedMarginLayout = new QVBoxLayout();
    stackedMarginLayout->setContentsMargins(0, 0, 0, 0);
    stackedMarginLayout->addLayout(m_pStackedLayout, 1);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(titleLabLayout, 0);
    layout->addLayout(stackedMarginLayout, 1);
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
    connect(m_pStartAllBtn, &QPushButton::clicked, this, &GifGenerationView::onStartAllClicked);
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
    m_pStackedLayout->setCurrentWidget(isNoData ? m_pImportGuideWidget : m_pContentWidget);
}

void GifGenerationView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->compressionOutPath());
    m_pOutputFolderCbb->addItem("...");
}

void GifGenerationView::GifGenerationView::setOutputFolder(const QString &path) {
    SETTINGS->setCompressionOutPath(path);
    m_pOutputFolderCbb->setItemText(0, path);
}

void GifGenerationView::initFrameRateCbbItem() {
    for(int i = GIFGENERATION_OUTPUT_MINFRAMERATE; i <= GIFGENERATION_OUTPUT_MAXFRAMERATE; i++) {
        m_pFrameRateCbb->addItem(QString::number(i));
    }
}

void GifGenerationView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Gif Maker"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pPixelsLbl->setText(tr("Pixels:"));
    m_pPixels_x_Lbl->setText("x");
    m_pFrameRateLbl->setText(tr("FrameRate:"));
    m_pPreviewBtn->setText(tr("Preview"));
    m_pStartAllBtn->setText(tr("create GIF"));
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

void GifGenerationView::onStartAllClicked() {
    GifGenerationPresenter *prst = dynamic_cast<GifGenerationPresenter *>(presenter());
    GifGenerationTask task;
    QList<QString> filePaths;
    for(auto data : prst->datas()) {
        filePaths.append(data.file_path);
    }
    GifGenerationParam param = {
        filePaths,
        SETTINGS->gifGenerationWidth(),
        SETTINGS->gifGenerationHeight(),
        SETTINGS->gifGenerationQuality(),
        SETTINGS->gifGenerationFps(),
        SETTINGS->gifGenerationRepeat(),
        SETTINGS->gifGenerationOutPath(),
    };
    task.exec(param);
}