#include "upsc/view.h"
#include "upsc/presenter.h"
#include "settings.h"

UpscView::UpscView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

ImportListView *UpscView::getImportListView() {
    return m_pImportListView;
}

void UpscView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    firstShow();
}

void UpscView::createUi() {
    setObjectName("UpscView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    //
    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setObjectName("UpscView_m_pTitleLbl");
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
    m_pSmapleWidget->setFixedHeight(134);
    auto smapleWidgetLayout = new QVBoxLayout(m_pSmapleWidget);
    smapleWidgetLayout->setContentsMargins(0, 0, 0, 0);
    smapleWidgetLayout->setSpacing(0);

    m_pSmapleTitleLbl = new QLabel(this);
    m_pSmapleTitleLbl->setAlignment(Qt::AlignCenter);

    m_pStandardSmapleImageLbl = new ClickableLabel(this);
    m_pStandardSmapleImageLbl->setFixedSize(100, 100);
    m_pStandardSmapleImageLbl = new ClickableLabel(this);
    m_pStandardSmapleImageLbl->setFixedSize(100, 100);
    m_pLiteSmapleImageLbl = new ClickableLabel(this);
    m_pLiteSmapleImageLbl->setFixedSize(100, 100);
    m_pFidelitySmapleImageLbl = new ClickableLabel(this);
    m_pFidelitySmapleImageLbl->setFixedSize(100, 100);
    m_pRemacriSmapleImageLbl = new ClickableLabel(this);
    m_pRemacriSmapleImageLbl->setFixedSize(100, 100);
    m_pUltramixSmapleImageLbl = new ClickableLabel(this);
    m_pUltramixSmapleImageLbl->setFixedSize(100, 100);
    m_pUltrasharpSmapleImageLbl = new ClickableLabel(this);
    m_pUltrasharpSmapleImageLbl->setFixedSize(100, 100);
    m_pDigitalSmapleImageLbl = new ClickableLabel(this);
    m_pDigitalSmapleImageLbl->setFixedSize(100, 100);

    auto sampleImageLayout = new QHBoxLayout();
    sampleImageLayout->setContentsMargins(0, 0, 0, 0);
    sampleImageLayout->setSpacing(14);
    sampleImageLayout->addStretch();
    sampleImageLayout->addWidget(m_pStandardSmapleImageLbl);
    sampleImageLayout->addWidget(m_pLiteSmapleImageLbl);
    sampleImageLayout->addWidget(m_pFidelitySmapleImageLbl);
    sampleImageLayout->addWidget(m_pRemacriSmapleImageLbl);
    sampleImageLayout->addWidget(m_pUltramixSmapleImageLbl);
    sampleImageLayout->addWidget(m_pUltrasharpSmapleImageLbl);
    sampleImageLayout->addWidget(m_pDigitalSmapleImageLbl);
    sampleImageLayout->addStretch();

    smapleWidgetLayout->addWidget(m_pSmapleTitleLbl);
    smapleWidgetLayout->addLayout(sampleImageLayout);

    importGuideLayout->addWidget(m_pImportGuide, 1);
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
    m_pRightWidget->setFixedWidth(320);
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
    m_pChooseModelLbl = new QLabel(this);
    m_pChooseModelLbl->setObjectName("UpscView_m_pChooseModelLbl");
    m_pChooseModelLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_pModelListView = new ListView<SUpscModelData>(this);
    m_pModelListView->setFixedHeight(360);
    m_pModelListView->setSpacing(8);
    m_pModelListDelegate = new UpscModelListDelegate(m_pModelListView);
    m_pModelListView->setItemDelegate(m_pModelListDelegate);
    m_pModelListView->viewport()->installEventFilter(m_pModelListDelegate);

    auto settingWidget = new QWidget(this);
    auto settingLWidget = new QWidget(this);
    auto settingRWidget = new QWidget(this);
    auto settingWidgetLayout = new QHBoxLayout(settingWidget);
    settingWidgetLayout->setContentsMargins(8, 8, 20, 0);
    settingWidgetLayout->setSpacing(8);
    settingWidgetLayout->addWidget(settingLWidget, 1);
    settingWidgetLayout->addWidget(settingRWidget, 1);

    auto settingLWidgetLayout = new QVBoxLayout(settingLWidget);
    settingLWidgetLayout->setContentsMargins(0, 0, 0, 0);
    settingLWidgetLayout->setSpacing(0);

    auto settingRWidgetLayout = new QVBoxLayout(settingRWidget);
    settingRWidgetLayout->setContentsMargins(0, 0, 0, 0);
    settingRWidgetLayout->setSpacing(0);

    m_pUpscaleLbl = new QLabel(this);
    m_pUpscaleLbl->setObjectName("UpscView_m_pUpscaleLbl");
    m_pUpscaleLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_pUpscaleCbb = new QComboBox(this);
    m_pUpscaleCbb->setFixedHeight(32);
    m_pUpscaleCbbFilter = new ComboBoxFilter(m_pUpscaleCbb);
    m_pUpscaleCbb->installEventFilter(m_pUpscaleCbbFilter);

    settingLWidgetLayout->addWidget(m_pUpscaleLbl);
    settingLWidgetLayout->addSpacing(4);
    settingLWidgetLayout->addWidget(m_pUpscaleCbb);

    m_pCustomOutputWidthCkb = new QCheckBox(this);
    m_pCustomOutputWidthLdt = new QLineEdit(this);
    settingRWidgetLayout->addWidget(m_pCustomOutputWidthCkb);
    settingRWidgetLayout->addSpacing(4);
    settingRWidgetLayout->addWidget(m_pCustomOutputWidthLdt);

    m_pCompressionLbl = new QLabel(this);
    m_pCompressionCbb = new QComboBox(this);
    settingLWidgetLayout->addSpacing(8);
    settingLWidgetLayout->addWidget(m_pCompressionLbl);
    settingLWidgetLayout->addSpacing(4);
    settingLWidgetLayout->addWidget(m_pCompressionCbb);

    m_pSaveAsFormatLbl = new QLabel(this);
    m_pSaveAsFormatCbb = new QComboBox(this);
    settingRWidgetLayout->addSpacing(8);
    settingRWidgetLayout->addWidget(m_pSaveAsFormatLbl);
    settingRWidgetLayout->addSpacing(4);
    settingRWidgetLayout->addWidget(m_pSaveAsFormatCbb);

    settingLWidgetLayout->addStretch();
    settingRWidgetLayout->addStretch();

    m_pExportBtn = new QPushButton(this);
    m_pExportBtn->setObjectName("UpscView_m_pExportBtn");
    m_pExportBtn->setFixedHeight(32);

    m_pOutputFolderLbl = new QLabel(this);
    m_pOutputFolderLbl->setObjectName("UpscView_pOutputFolderLbl");

    m_pOutputFolderCbb = new QComboBox(this);
    m_pOutputFolderCbb->setFixedSize(240, 24);

    m_pOutputFolderCbbFilter = new ComboBoxFilter(m_pOutputFolderCbb);
    m_pOutputFolderCbb->installEventFilter(m_pOutputFolderCbbFilter);

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

    rightWidgetLayout->addWidget(m_pChooseModelLbl);
    rightWidgetLayout->addWidget(m_pModelListView);
    rightWidgetLayout->addWidget(settingWidget);
    rightWidgetLayout->addStretch();
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

void UpscView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &UpscView::onLanguageChange);
    connect(m_pStandardSmapleImageLbl, &ClickableLabel::sigClicked, this, &UpscView::onStandardSmapleImageLblClicked);
    connect(m_pLiteSmapleImageLbl, &ClickableLabel::sigClicked, this, &UpscView::onLiteSmapleImageLblClicked);
    connect(m_pFidelitySmapleImageLbl, &ClickableLabel::sigClicked, this, &UpscView::onFidelitySmapleImageLblClicked);
    connect(m_pRemacriSmapleImageLbl, &ClickableLabel::sigClicked, this, &UpscView::onRemacriSmapleImageLblClicked);
    connect(m_pUltramixSmapleImageLbl, &ClickableLabel::sigClicked, this, &UpscView::onUltramixSmapleImageLblClicked);
    connect(m_pUltrasharpSmapleImageLbl, &ClickableLabel::sigClicked, this, &UpscView::onUltrasharpSmapleImageLblClicked);
    connect(m_pDigitalSmapleImageLbl, &ClickableLabel::sigClicked, this, &UpscView::onDigitalSmapleImageLblClicked);
    connect(m_pImportListView, &ImportListView::sigImportListCountChange, this, &UpscView::onImportListCountChange);
    connect(m_pImportListView, &ImportListView::sigImportListCurrentChanged, this, &UpscView::onImportListCurrentChanged);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &UpscView::onGuideImportFile);
    connect(m_pModelListView, &AbstractListView::sigCurrentChanged, this, &UpscView::ondModelListViewCurrentChanged);
    connect(m_pExportBtn, &QPushButton::clicked, this, &UpscView::onExportBtnClicked);
}

void UpscView::firstShow() {
    static bool firstShow = true;
    if(firstShow) {
        firstShow = false;
        loadSampleImage();
        initOutputFolderCbbItem();
        loadModelList();
        initUpscaleCbbItem();
        initCompressionCbbItem();
        initSaveAsFormatCbbItem();
    }
}

void UpscView::loadSampleImage() {
    UpscPresenter *prst = dynamic_cast<UpscPresenter *>(presenter());
    m_pStandardSmapleImageLbl->setPixmap(QPixmap(prst->getSampleImagePath(EUpscSmapleType_Standard)).scaled(m_pStandardSmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pLiteSmapleImageLbl->setPixmap(QPixmap(prst->getSampleImagePath(EUpscSmapleType_Lite)).scaled(m_pLiteSmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pFidelitySmapleImageLbl->setPixmap(QPixmap(prst->getSampleImagePath(EUpscSmapleType_Fidelity)).scaled(m_pFidelitySmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pRemacriSmapleImageLbl->setPixmap(QPixmap(prst->getSampleImagePath(EUpscSmapleType_Remacri)).scaled(m_pRemacriSmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pUltramixSmapleImageLbl->setPixmap(QPixmap(prst->getSampleImagePath(EUpscSmapleType_Ultramix)).scaled(m_pUltramixSmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pUltrasharpSmapleImageLbl->setPixmap(QPixmap(prst->getSampleImagePath(EUpscSmapleType_Ultrasharp)).scaled(m_pUltrasharpSmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pDigitalSmapleImageLbl->setPixmap(QPixmap(prst->getSampleImagePath(EUpscSmapleType_Digital)).scaled(m_pDigitalSmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void UpscView::importSampleImage(EUpscSmapleType type) {
    UpscPresenter *prst = dynamic_cast<UpscPresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImagePath(type));
    m_pImportListView->importFile(paths);
}

void UpscView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->upscOutPath());
}

void UpscView::loadModelList() {
    UpscPresenter *prst = dynamic_cast<UpscPresenter *>(presenter());
    m_pModelListView->changeData(prst->getModelDatas());
    setModelListCurrentIndex(0);
}

void UpscView::gotoImportGuide() {
    m_pStackedLayout->setCurrentWidget(m_pImportGuideWidget);
}

void UpscView::gotoWorkspace() {
    m_pStackedLayout->setCurrentWidget(m_pWorkspaceWidget);
}

void UpscView::imageViewerLoad(const QString &filePath) {
    m_pImageViewer->loadImage(filePath);
}

void UpscView::setModelListCurrentIndex(int index) {
    QModelIndex modelIndex = m_pModelListView->model()->index(index, 0);
    m_pModelListView->setCurrentIndex(modelIndex);
}

void UpscView::initUpscaleCbbItem() {
    QStringList texts;
    texts.append("1x");
    texts.append("2x");
    texts.append("4x");
    texts.append("8x");
    m_pUpscaleCbb->addItems(texts);
}

void UpscView::upscaleSettingVisible(bool visible) {
    m_pUpscaleLbl->setVisible(visible);
    m_pUpscaleCbb->setVisible(visible);
}

void UpscView::initCompressionCbbItem() {
    QStringList texts;
    texts.append("0%");
    texts.append("10%");
    texts.append("20%");
    texts.append("30%");
    texts.append("40%");
    texts.append("50%");
    texts.append("60%");
    texts.append("70%");
    texts.append("80%");
    texts.append("90%");
    texts.append("100%");
    m_pCompressionCbb->addItems(texts);
}

void UpscView::initSaveAsFormatCbbItem() {
    QStringList texts;
    texts.append("png");
    texts.append("jpg");
    texts.append("jpeg");
    texts.append("webp");
    m_pSaveAsFormatCbb->addItems(texts);
}

void UpscView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Ai Image Enhancer"));
    m_pSmapleTitleLbl->setText(tr("Try with one of our smaples!"));
    m_pChooseModelLbl->setText(tr("Choose AI Model"));
    m_pUpscaleLbl->setText(tr("Upscaler Setting"));
    m_pCustomOutputWidthCkb->setText(tr("Custom width"));
    m_pCompressionLbl->setText(tr("Compression"));
    m_pSaveAsFormatLbl->setText(tr("Save as format"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pExportBtn->setText(tr("Export"));
}

void UpscView::onStandardSmapleImageLblClicked() {
    importSampleImage(EUpscSmapleType_Standard);
}

void UpscView::onLiteSmapleImageLblClicked() {
    importSampleImage(EUpscSmapleType_Lite);
}

void UpscView::onFidelitySmapleImageLblClicked() {
    importSampleImage(EUpscSmapleType_Fidelity);
}

void UpscView::onRemacriSmapleImageLblClicked() {
    importSampleImage(EUpscSmapleType_Remacri);
}

void UpscView::onUltramixSmapleImageLblClicked() {
    importSampleImage(EUpscSmapleType_Ultramix);
}

void UpscView::onUltrasharpSmapleImageLblClicked() {
    importSampleImage(EUpscSmapleType_Ultrasharp);
}

void UpscView::onDigitalSmapleImageLblClicked() {
    importSampleImage(EUpscSmapleType_Digital);
}

void UpscView::onImportListCountChange(int count) {
    if(count > 0) {
        gotoWorkspace();
    } else {
        gotoImportGuide();
    }
}

void UpscView::onImportListCurrentChanged(const QString filePath) {
    imageViewerLoad(filePath);
}

void UpscView::onGuideImportFile(const QStringList &filePaths) {
    UpscPresenter *prst = dynamic_cast<UpscPresenter *>(presenter());
    m_pImportListView->importFile(filePaths);
}

void UpscView::ondModelListViewCurrentChanged(const QModelIndex &current, const QModelIndex &previous) {
    auto data = current.data(Qt::UserRole).value<SUpscModelData>();
    upscaleSettingVisible(data.id == 5);
}

void UpscView::onExportBtnClicked() {
    UpscPresenter *prst = dynamic_cast<UpscPresenter *>(presenter());
    prst->Upsc();
}