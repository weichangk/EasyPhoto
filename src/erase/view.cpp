#include "erase/view.h"
#include "erase/presenter.h"
#include "settings.h"

EraseView::EraseView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

ImportListView *EraseView::getImportListView() {
    return m_pImportListView;
}

void EraseView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    firstShow();
}

void EraseView::createUi() {
    setObjectName("EraseView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    //
    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setObjectName("EraseView_m_pTitleLbl");
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
    m_pExportBtn = new QPushButton(this);
    m_pExportBtn->setObjectName("EraseView_m_pExportBtn");
    m_pExportBtn->setFixedHeight(32);

    m_pOutputFolderLbl = new QLabel(this);
    m_pOutputFolderLbl->setObjectName("EraseView_pOutputFolderLbl");

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

void EraseView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &EraseView::onLanguageChange);
    connect(m_pSmaple1ImageLbl, &ClickableLabel::sigClicked, this, &EraseView::onSmaple1ImageLblClicked);
    connect(m_pSmaple2ImageLbl, &ClickableLabel::sigClicked, this, &EraseView::onSmaple2ImageLblClicked);
    connect(m_pImportListView, &ImportListView::sigImportListCountChange, this, &EraseView::onImportListCountChange);
    connect(m_pImportListView, &ImportListView::sigImportListCurrentChanged, this, &EraseView::onImportListCurrentChanged);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &EraseView::onGuideImportFile);
}

void EraseView::firstShow() {
    static bool firstShow = true;
    if(firstShow) {
        firstShow = false;
        loadSampleImage();
        initOutputFolderCbbItem();
    }
}

void EraseView::loadSampleImage() {
    ErasePresenter *prst = dynamic_cast<ErasePresenter *>(presenter());
    m_pSmaple1ImageLbl->setPixmap(QPixmap(prst->getSampleImage1Path()).scaled(m_pSmaple1ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pSmaple2ImageLbl->setPixmap(QPixmap(prst->getSampleImage2Path()).scaled(m_pSmaple2ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void EraseView::importSampleImage1() {
    ErasePresenter *prst = dynamic_cast<ErasePresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImage1Path());
    m_pImportListView->importFile(paths);
}

void EraseView::importSampleImage2() {
    ErasePresenter *prst = dynamic_cast<ErasePresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImage2Path());
    m_pImportListView->importFile(paths);
}

void EraseView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->getEraseSetting()->getOutPath());
}

void EraseView::gotoImportGuide() {
    m_pStackedLayout->setCurrentWidget(m_pImportGuideWidget);
}

void EraseView::gotoWorkspace() {
    m_pStackedLayout->setCurrentWidget(m_pWorkspaceWidget);
}

void EraseView::imageViewerLoad(const QString &filePath) {
    m_pImageViewer->loadImage(filePath);
}

void EraseView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Watermaker Eraser"));
    m_pSmapleTitleLbl->setText(tr("Try with one of our smaples!"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pExportBtn->setText(tr("Export"));
}

void EraseView::onSmaple1ImageLblClicked() {
    importSampleImage1();
}

void EraseView::onSmaple2ImageLblClicked() {
    importSampleImage2();
}

void EraseView::onImportListCountChange(int count) {
    if(count > 0) {
        gotoWorkspace();
    } else {
        gotoImportGuide();
    }
}

void EraseView::onImportListCurrentChanged(const QString filePath) {
    imageViewerLoad(filePath);
}

void EraseView::onGuideImportFile(const QStringList &filePaths) {
    ErasePresenter *prst = dynamic_cast<ErasePresenter *>(presenter());
    m_pImportListView->importFile(filePaths);
}