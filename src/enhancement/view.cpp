#include "enhancement/view.h"
#include "enhancement/presenter.h"
#include "settings.h"

EnhancementView::EnhancementView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

ImportListView *EnhancementView::getImportListView() {
    return m_pImportListView;
}

void EnhancementView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    firstShow();
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
    auto rightWidgetLayout = new QVBoxLayout(m_pRightWidget);
    rightWidgetLayout->setContentsMargins(0, 0, 0, 0);
    rightWidgetLayout->setSpacing(0);

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

    m_pWorkspaceWidget = new QWidget(this);
    QVBoxLayout *workspaceWidgetLayout = new QVBoxLayout(m_pWorkspaceWidget);
    workspaceWidgetLayout->setContentsMargins(0, 0, 0, 0);
    workspaceWidgetLayout->setSpacing(0);

    m_pImageViewer = new ImageViewer(this);
    m_pImportListView = new ImportListView(this);

    workspaceWidgetLayout->addWidget(m_pImageViewer, 1);
    workspaceWidgetLayout->addWidget(m_pImportListView);

    m_pLeftWidgetStackedLayout->addWidget(m_pImportGuideWidget);
    m_pLeftWidgetStackedLayout->addWidget(m_pWorkspaceWidget);

    auto leftWidgetStackedMarginLayout = new QVBoxLayout();
    leftWidgetStackedMarginLayout->setContentsMargins(0, 0, 0, 0);
    leftWidgetStackedMarginLayout->addLayout(m_pLeftWidgetStackedLayout, 1);

    LeftWidgetLayout->addLayout(leftWidgetStackedMarginLayout, 1);

    m_pChooseModelLbl = new QLabel(this);
    m_pChooseModelLbl->setObjectName("EnhancementView_m_pChooseModelLbl");
    m_pChooseModelLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_pModelListView = new ListView<SEnhanceModelData>(this);
    m_pModelListView->setSpacing(8);
    m_pModelListDelegate = new EnhanceModelListDelegate(m_pModelListView);
    m_pModelListView->setItemDelegate(m_pModelListDelegate);
    m_pModelListView->viewport()->installEventFilter(m_pModelListDelegate);

    m_pExportBtn = new QPushButton(this);
    m_pExportBtn->setObjectName("EnhancementView_m_pExportBtn");
    m_pExportBtn->setFixedHeight(32);

    m_pOutputFolderLbl = new QLabel(this);
    m_pOutputFolderLbl->setObjectName("EnhancementView_pOutputFolderLbl");

    m_pOutputFolderCbb = new QComboBox(this);
    m_pOutputFolderCbb->setFixedSize(240, 24);

    m_pOutputFolderCbbFilter = new ComboBoxFilter(m_pOutputFolderCbb);
    m_pOutputFolderCbb->installEventFilter(m_pOutputFolderCbbFilter);

    m_pOpenOutputFolderBtn = new IconButton(this);
    m_pOpenOutputFolderBtn->setFixedSize(24, 24);
    m_pOpenOutputFolderBtn->setIconSize(24, 24);
    m_pOpenOutputFolderBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/old/icon/icon_state/icon24/icon24_file.png");

    auto outputFolderLayout = new QHBoxLayout();
    outputFolderLayout->setContentsMargins(0, 0, 0, 0);
    outputFolderLayout->setSpacing(0);

    outputFolderLayout->addWidget(m_pOutputFolderLbl);
    outputFolderLayout->addWidget(m_pOutputFolderCbb, 1);
    outputFolderLayout->addStretch();
    outputFolderLayout->addWidget(m_pOpenOutputFolderBtn);

    rightWidgetLayout->addWidget(m_pChooseModelLbl);
    rightWidgetLayout->addWidget(m_pModelListView, 1);
    rightWidgetLayout->addStretch();
    rightWidgetLayout->addWidget(m_pExportBtn);
    rightWidgetLayout->addLayout(outputFolderLayout);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(titleLabLayout, 0);
    layout->addWidget(m_pBodyWidget, 1);
}

void EnhancementView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &EnhancementView::onLanguageChange);
    connect(m_pSmaple1ImageLbl, &ClickableLabel::sigClicked, this, &EnhancementView::onSmaple1ImageLblClicked);
    connect(m_pSmaple2ImageLbl, &ClickableLabel::sigClicked, this, &EnhancementView::onSmaple2ImageLblClicked);
    connect(m_pImportListView, &ImportListView::sigImportListCountChange, this, &EnhancementView::onImportListCountChange);
    connect(m_pImportListView, &ImportListView::sigImportListCurrentChanged, this, &EnhancementView::onImportListCurrentChanged);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &EnhancementView::onGuideImportFile);
}

void EnhancementView::firstShow() {
    static bool firstShow = true;
    if(firstShow) {
        firstShow = false;
        loadSampleImage();
        initOutputFolderCbbItem();
        loadModelList();
    }
}

void EnhancementView::loadSampleImage() {
    EnhancementPresenter *prst = dynamic_cast<EnhancementPresenter *>(presenter());
    m_pSmaple1ImageLbl->setPixmap(QPixmap(prst->getSampleImage1Path()).scaled(m_pSmaple1ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pSmaple2ImageLbl->setPixmap(QPixmap(prst->getSampleImage2Path()).scaled(m_pSmaple2ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void EnhancementView::importSampleImage1() {
    EnhancementPresenter *prst = dynamic_cast<EnhancementPresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImage1Path());
    m_pImportListView->importFile(paths);
}

void EnhancementView::importSampleImage2() {
    EnhancementPresenter *prst = dynamic_cast<EnhancementPresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImage2Path());
    m_pImportListView->importFile(paths);
}

void EnhancementView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->enhanceOutPath());
}

void EnhancementView::loadModelList() {
    EnhancementPresenter *prst = dynamic_cast<EnhancementPresenter *>(presenter());
    m_pModelListView->changeData(prst->getModelDatas());
}

void EnhancementView::gotoImportGuide() {
    m_pLeftWidgetStackedLayout->setCurrentWidget(m_pImportGuideWidget);
}

void EnhancementView::gotoWorkspace() {
    m_pLeftWidgetStackedLayout->setCurrentWidget(m_pWorkspaceWidget);
}

void EnhancementView::imageViewerLoad(const QString &filePath) {
    m_pImageViewer->loadImage(filePath);
}

void EnhancementView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Ai Image Enhancer"));
    m_pSmapleTitleLbl->setText(tr("Try with one of our smaples!"));
    m_pChooseModelLbl->setText(tr("Choose AI Model"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pExportBtn->setText(tr("Export"));
}

void EnhancementView::onSmaple1ImageLblClicked() {
    importSampleImage1();
}

void EnhancementView::onSmaple2ImageLblClicked() {
    importSampleImage2();
}

void EnhancementView::onImportListCountChange(int count) {
    if(count > 0) {
        gotoWorkspace();
    } else {
        gotoImportGuide();
    }
}

void EnhancementView::onImportListCurrentChanged(const QString filePath) {
    imageViewerLoad(filePath);
}

void EnhancementView::onGuideImportFile(const QStringList &filePaths) {
    EnhancementPresenter *prst = dynamic_cast<EnhancementPresenter *>(presenter());
    m_pImportListView->importFile(filePaths);
}