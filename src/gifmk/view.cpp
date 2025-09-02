#include "gifmk/view.h"
#include "gifmk/presenter.h"
#include "gifmk/task.h"
#include "settings.h"
#include "message/funcchangemessage.h"
#include "funcenum.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>

GifMkView::GifMkView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

ImportListView *GifMkView::getImportListView() {
    return m_pImportListView;
}

void GifMkView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    firstShow();
    initFrameRateCbbItem();
}

void GifMkView::createUi() {
    setObjectName("GifMkView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    //
    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setObjectName("GifMkView_m_pTitleLbl");
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
    m_pWorkspaceWidget = new QWidget(this);
    auto bodyWidgetLayout = new QHBoxLayout(m_pWorkspaceWidget);
    bodyWidgetLayout->setContentsMargins(0, 0, 0, 0);
    bodyWidgetLayout->setSpacing(0);

    m_pLeftWidget = new QWidget(this);
    auto LeftWidgetLayout = new QVBoxLayout(m_pLeftWidget);
    LeftWidgetLayout->setContentsMargins(0, 0, 0, 0);
    LeftWidgetLayout->setSpacing(0);

    m_pRightWidget = new QWidget(this);
    m_pRightWidget->setFixedWidth(240);
    auto rightWidgetLayout = new QVBoxLayout(m_pRightWidget);
    rightWidgetLayout->setContentsMargins(20, 24, 20, 24);
    rightWidgetLayout->setSpacing(0);

    bodyWidgetLayout->addWidget(m_pLeftWidget, 1);
    bodyWidgetLayout->addWidget(m_pRightWidget);

    //
    m_pImageViewer = new ImageViewer(this);
    m_pImportListView = new ImportListView(this);
    LeftWidgetLayout->addWidget(m_pImageViewer, 1);
    LeftWidgetLayout->addWidget(m_pImportListView);

    //
    m_pPixelsLbl = new QLabel(this);
    m_pPixelsLbl->setObjectName("GifMkView_m_pPixelsLbl");
    rightWidgetLayout->addWidget(m_pPixelsLbl);

    m_pPixelsWidthLdt = new QLineEdit(this);
    m_pPixelsWidthLdt->setFixedSize(48, 24);
    m_pPixels_x_Lbl = new QLabel(this);
    m_pPixels_x_Lbl->setObjectName("GifMkView_m_pPixels_x_Lbl");
    m_pPixelsHeightLdt = new QLineEdit(this);
    m_pPixelsHeightLdt->setFixedSize(48, 24);

    auto pixelsLayout = new QHBoxLayout();
    pixelsLayout->setContentsMargins(0, 0, 0, 0);
    pixelsLayout->addWidget(m_pPixelsWidthLdt);
    pixelsLayout->addWidget(m_pPixels_x_Lbl);
    pixelsLayout->addWidget(m_pPixelsHeightLdt);
    pixelsLayout->addStretch();
    rightWidgetLayout->addLayout(pixelsLayout);

    rightWidgetLayout->addSpacing(20);

    m_pFrameRateLbl = new QLabel(this);
    m_pFrameRateLbl->setObjectName("GifMkView_m_pFrameRateLbl");
    rightWidgetLayout->addWidget(m_pFrameRateLbl);
    m_pFrameRateCbb = new QComboBox(this);
    rightWidgetLayout->addWidget(m_pFrameRateCbb);

    rightWidgetLayout->addSpacing(20);

    m_pOutputFolderLbl = new QLabel(this);
    m_pOutputFolderLbl->setObjectName("GifMkView_m_pOutputFolderLbl");
    rightWidgetLayout->addWidget(m_pOutputFolderLbl);

    m_pOutputFolderCbb = new QComboBox(this);
    m_pOutputFolderCbb->setFixedHeight(24);

    m_pOpenOutputFolderBtn = new IconButton(this);
    m_pOpenOutputFolderBtn->setFixedSize(24, 24);
    m_pOpenOutputFolderBtn->setIconSize(24, 24);
    m_pOpenOutputFolderBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_file.png");

    auto folderLayout = new QHBoxLayout();
    folderLayout->setContentsMargins(0, 0, 0, 0);
    folderLayout->addWidget(m_pOutputFolderCbb, 1);
    folderLayout->addWidget(m_pOpenOutputFolderBtn);
    rightWidgetLayout->addLayout(folderLayout);

    rightWidgetLayout->addStretch();

    m_pPreviewBtn = new QPushButton(this);
    m_pPreviewBtn->setObjectName("GifMkView_m_pPreviewBtn");
    m_pPreviewBtn->setFixedHeight(32);
    rightWidgetLayout->addWidget(m_pPreviewBtn);

    rightWidgetLayout->addSpacing(10);

    m_pStartAllBtn = new QPushButton(this);
    m_pStartAllBtn->setObjectName("GifMkView_m_pStartAllBtn");
    m_pStartAllBtn->setFixedHeight(32);
    rightWidgetLayout->addWidget(m_pStartAllBtn);

    //
    m_pStackedLayout = new QStackedLayout();
    m_pStackedLayout->addWidget(m_pImportGuideWidget);
    m_pStackedLayout->addWidget(m_pWorkspaceWidget);

    auto stackedMarginLayout = new QVBoxLayout();
    stackedMarginLayout->setContentsMargins(0, 0, 0, 0);
    stackedMarginLayout->addLayout(m_pStackedLayout, 1);

    //
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(titleLabLayout, 0);
    layout->addLayout(stackedMarginLayout, 1);
}

void GifMkView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &GifMkView::onLanguageChange);
    connect(m_pOutputFolderCbb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &GifMkView::onOutputFolderCbbIndexChanged);
    connect(m_pOpenOutputFolderBtn, &QPushButton::clicked, this, &GifMkView::onOpenOutputFolderBtnClicked);
    connect(m_pPreviewBtn, &QPushButton::clicked, this, &GifMkView::onPreviewBtnClicked);
    connect(m_pStartAllBtn, &QPushButton::clicked, this, &GifMkView::onStartAllClicked);
    connect(m_pImportListView, &ImportListView::sigImportListCountChange, this, &GifMkView::onImportListCountChange);
    connect(m_pImportListView, &ImportListView::sigImportListCurrentChanged, this, &GifMkView::onImportListCurrentChanged);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &GifMkView::onGuideImportFile);
}

void GifMkView::firstShow() {
    static bool firstShow = true;
    if (firstShow) {
        firstShow = false;
        initOutputFolderCbbItem();
        initFrameRateCbbItem();
    }
}

QWidget *GifMkView::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("GifMkView_DividingLine");
    dividingLine->setFixedHeight(1);
    return dividingLine;
}

void GifMkView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->compressionOutPath());
    m_pOutputFolderCbb->addItem("...");
}

void GifMkView::setOutputFolder(const QString &path) {
    SETTINGS->setCompressionOutPath(path);
    m_pOutputFolderCbb->setItemText(0, path);
}

void GifMkView::initFrameRateCbbItem() {
    for (int i = GIFGENERATION_OUTPUT_MINFRAMERATE; i <= GIFGENERATION_OUTPUT_MAXFRAMERATE; i++) {
        m_pFrameRateCbb->addItem(QString::number(i));
    }
}

void GifMkView::gotoImportGuide() {
    m_pStackedLayout->setCurrentWidget(m_pImportGuideWidget);
}

void GifMkView::gotoWorkspace() {
    m_pStackedLayout->setCurrentWidget(m_pWorkspaceWidget);
}

void GifMkView::imageViewerLoad(const QString &filePath) {
    m_pImageViewer->loadImage(filePath);
}

void GifMkView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Gif Maker"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pPixelsLbl->setText(tr("Pixels:"));
    m_pPixels_x_Lbl->setText("x");
    m_pFrameRateLbl->setText(tr("FrameRate:"));
    m_pPreviewBtn->setText(tr("Preview"));
    m_pStartAllBtn->setText(tr("create GIF"));
}

void GifMkView::onOutputFolderCbbIndexChanged(int index) {
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

void GifMkView::onOpenOutputFolderBtnClicked() {
    QString folderPath = SETTINGS->compressionOutPath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
}

void GifMkView::onPreviewBtnClicked() {
    FuncChangeMessage msg(EFunc::FuncGifPreview);
    presenter()->sendMessage(&msg);
}

void GifMkView::onStartAllClicked() {
    GifMkPresenter *prst = dynamic_cast<GifMkPresenter *>(presenter());
    ImgKitCore::GIFMK::Task task;
    QList<QString> filePaths;
    for (auto data : prst->getDatas()) {
        filePaths.append(data.path);
    }
    ImgKitCore::GIFMK::SParam param = {
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

void GifMkView::onImportListCountChange(int count) {
    if (count > 0) {
        gotoWorkspace();
    } else {
        gotoImportGuide();
    }
}

void GifMkView::onImportListCurrentChanged(const QString filePath) {
    imageViewerLoad(filePath);
}

void GifMkView::onGuideImportFile(const QStringList &filePaths) {
    GifMkPresenter *prst = dynamic_cast<GifMkPresenter *>(presenter());
    m_pImportListView->importFile(filePaths);
}