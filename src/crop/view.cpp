#include "crop/view.h"
#include "crop/presenter.h"
#include "settings.h"

CropView::CropView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

ImportListView *CropView::getImportListView() {
    return m_pImportListView;
}

void CropView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    firstShow();
}

void CropView::createUi() {
    setObjectName("CropView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    //
    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setObjectName("CropView_m_pTitleLbl");
    auto titleLabLayout = new QHBoxLayout();
    titleLabLayout->setContentsMargins(20, 0, 0, 0);
    titleLabLayout->addWidget(m_pTitleLbl, 0, Qt::AlignLeft);

    //
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

    m_pSmaple1ImageLbl = new ClickableLabel(this);
    m_pSmaple1ImageLbl->setFixedSize(128, 72);
    m_pSmaple2ImageLbl = new ClickableLabel(this);
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
    m_pRightWidget->setFixedWidth(270);
    auto rightWidgetLayout = new QVBoxLayout(m_pRightWidget);
    rightWidgetLayout->setContentsMargins(0, 0, 0, 0);
    rightWidgetLayout->setSpacing(0);

    bodyWidgetLayout->addWidget(m_pLeftWidget, 1);
    bodyWidgetLayout->addWidget(m_pRightWidget);

    //
    m_pImageViewer = new ImageViewer(this);
    m_pImportListView = new ImportListView(this);
    LeftWidgetLayout->addWidget(m_pImageViewer, 1);
    LeftWidgetLayout->addWidget(m_pImportListView);

    //
    m_pCropSizeLbl = new QLabel(this);
    m_pCropSizeLbl->setObjectName("CropView_m_pCropSizeLbl");
    rightWidgetLayout->addWidget(m_pCropSizeLbl);

    //
    m_pCropScaleListView = new ListView<SCropScaleData>(this);
    m_pCropScaleListView->setSpacing(0);
    m_pScalelListDelegate = new ScalelListDelegate(m_pCropScaleListView);
    m_pCropScaleListView->setItemDelegate(m_pScalelListDelegate);
    m_pCropScaleListView->viewport()->installEventFilter(m_pScalelListDelegate);
    rightWidgetLayout->addWidget(m_pCropScaleListView);
    // m_pCropScaleListView->changeData(formatDatas);

    //
    m_pPixelsWidthLdt = new QLineEdit(this);
    m_pPixelsWidthLdt->setFixedSize(72, 24);
    m_pLockScaleBtn = new IconButton(this);
    m_pLockScaleBtn->setFixedSize(24, 24);
    m_pLockScaleBtn->setIconSize(24, 24);
    m_pLockScaleBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_file.png");
    m_pPixelsHeightLdt = new QLineEdit(this);
    m_pPixelsHeightLdt->setFixedSize(72, 24);

    auto pixelsLayout = new QHBoxLayout();
    pixelsLayout->setContentsMargins(0, 0, 0, 0);
    pixelsLayout->addWidget(m_pPixelsWidthLdt);
    pixelsLayout->addStretch();
    pixelsLayout->addWidget(m_pLockScaleBtn);
    pixelsLayout->addStretch();
    pixelsLayout->addWidget(m_pPixelsHeightLdt);
    rightWidgetLayout->addLayout(pixelsLayout);

    //
    rightWidgetLayout->addSpacing(16);

    //
    m_pRotateAndFlipLbl = new QLabel(this);
    m_pRotateAndFlipLbl->setObjectName("CropView_m_pRotateAndFlipLbl");
    rightWidgetLayout->addWidget(m_pRotateAndFlipLbl);

    //
    m_pRotateRight90Btn = new IconButton(this);
    m_pRotateRight90Btn->setFixedSize(24, 24);
    m_pRotateRight90Btn->setIconSize(24, 24);
    m_pRotateRight90Btn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_file.png");
    m_pRotateLeft90Btn = new IconButton(this);
    m_pRotateLeft90Btn->setFixedSize(24, 24);
    m_pRotateLeft90Btn->setIconSize(24, 24);
    m_pRotateLeft90Btn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_file.png");
    m_pFlipHorBtn = new IconButton(this);
    m_pFlipHorBtn->setFixedSize(24, 24);
    m_pFlipHorBtn->setIconSize(24, 24);
    m_pFlipHorBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_file.png");
    m_pFlipVErBtn = new IconButton(this);
    m_pFlipVErBtn->setFixedSize(24, 24);
    m_pFlipVErBtn->setIconSize(24, 24);
    m_pFlipVErBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_file.png");
    auto rotateBtnLayout = new QHBoxLayout();
    rotateBtnLayout->setContentsMargins(0, 0, 0, 0);
    rotateBtnLayout->addWidget(m_pRotateRight90Btn);
    rotateBtnLayout->addWidget(m_pRotateLeft90Btn);
    rotateBtnLayout->addWidget(m_pFlipHorBtn);
    rotateBtnLayout->addWidget(m_pFlipVErBtn);
    rightWidgetLayout->addLayout(rotateBtnLayout);

    //
    rightWidgetLayout->addSpacing(16);

    //
    m_pApplySameCkb = new QCheckBox(this);

    //
    m_pResetBtn = new IconButton(this);
    m_pResetBtn->setFixedSize(24, 24);
    m_pResetBtn->setIconSize(24, 24);
    m_pResetBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_file.png");

    //
    auto applySameLayout = new QHBoxLayout();
    applySameLayout->setContentsMargins(0, 0, 0, 0);
    applySameLayout->addWidget(m_pApplySameCkb);
    applySameLayout->addStretch();
    applySameLayout->addWidget(m_pResetBtn);
    rightWidgetLayout->addLayout(applySameLayout);

    //
    rightWidgetLayout->addStretch();

    //
    m_pExportBtn = new QPushButton(this);
    m_pExportBtn->setObjectName("CropView_m_pExportBtn");
    m_pExportBtn->setFixedHeight(32);

    m_pOutputFolderLbl = new QLabel(this);
    m_pOutputFolderLbl->setObjectName("CropView_pOutputFolderLbl");

    m_pOutputFolderCbb = new QComboBox(this);
    m_pOutputFolderCbb->setFixedSize(240, 24);

    m_pOpenOutputFolderBtn = new IconButton(this);
    m_pOpenOutputFolderBtn->setFixedSize(24, 24);
    m_pOpenOutputFolderBtn->setIconSize(24, 24);
    m_pOpenOutputFolderBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_file.png");

    auto outputFolderLayout = new QHBoxLayout();
    outputFolderLayout->setContentsMargins(0, 0, 0, 0);
    outputFolderLayout->setSpacing(0);

    outputFolderLayout->addWidget(m_pOutputFolderLbl);
    outputFolderLayout->addWidget(m_pOutputFolderCbb, 1);
    outputFolderLayout->addStretch();
    outputFolderLayout->addWidget(m_pOpenOutputFolderBtn);

    rightWidgetLayout->addWidget(m_pExportBtn);
    rightWidgetLayout->addLayout(outputFolderLayout);

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

void CropView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &CropView::onLanguageChange);
    connect(m_pSmaple1ImageLbl, &ClickableLabel::sigClicked, this, &CropView::onSmaple1ImageLblClicked);
    connect(m_pSmaple2ImageLbl, &ClickableLabel::sigClicked, this, &CropView::onSmaple2ImageLblClicked);
    connect(m_pImportListView, &ImportListView::sigImportListCountChange, this, &CropView::onImportListCountChange);
    connect(m_pImportListView, &ImportListView::sigImportListCurrentChanged, this, &CropView::onImportListCurrentChanged);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &CropView::onGuideImportFile);
}

void CropView::firstShow() {
    static bool firstShow = true;
    if(firstShow) {
        firstShow = false;
        loadSampleImage();
        initOutputFolderCbbItem();
    }
}

void CropView::loadSampleImage() {
    CropPresenter *prst = dynamic_cast<CropPresenter *>(presenter());
    m_pSmaple1ImageLbl->setPixmap(QPixmap(prst->getSampleImage1Path()).scaled(m_pSmaple1ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pSmaple2ImageLbl->setPixmap(QPixmap(prst->getSampleImage2Path()).scaled(m_pSmaple2ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void CropView::importSampleImage1() {
    CropPresenter *prst = dynamic_cast<CropPresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImage1Path());
    m_pImportListView->importFile(paths);
}

void CropView::importSampleImage2() {
    CropPresenter *prst = dynamic_cast<CropPresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImage2Path());
    m_pImportListView->importFile(paths);
}

void CropView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->getCropSetting()->getOutPath());
}

void CropView::gotoImportGuide() {
    m_pStackedLayout->setCurrentWidget(m_pImportGuideWidget);
}

void CropView::gotoWorkspace() {
    m_pStackedLayout->setCurrentWidget(m_pWorkspaceWidget);
}

void CropView::imageViewerLoad(const QString &filePath) {
    m_pImageViewer->loadImage(filePath);
}

void CropView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Image Cropper"));
    m_pCropSizeLbl->setText(tr("Crop Size"));
    m_pRotateAndFlipLbl->setText(tr("Rotate and Flip"));
    m_pApplySameCkb->setText(tr("Apply same to all images"));
    m_pSmapleTitleLbl->setText(tr("Try with one of our smaples!"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pExportBtn->setText(tr("Export"));
}

void CropView::onSmaple1ImageLblClicked() {
    importSampleImage1();
}

void CropView::onSmaple2ImageLblClicked() {
    importSampleImage2();
}

void CropView::onImportListCountChange(int count) {
    if(count > 0) {
        gotoWorkspace();
    } else {
        gotoImportGuide();
    }
}

void CropView::onImportListCurrentChanged(const QString filePath) {
    imageViewerLoad(filePath);
}

void CropView::onGuideImportFile(const QStringList &filePaths) {
    CropPresenter *prst = dynamic_cast<CropPresenter *>(presenter());
    m_pImportListView->importFile(filePaths);
}