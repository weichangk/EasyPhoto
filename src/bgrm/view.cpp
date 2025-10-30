#include "bgrm/view.h"
#include "bgrm/presenter.h"
#include "settings.h"
#include "core/theme.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>

BgRmView::BgRmView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

ImportListView *BgRmView::getImportListView() {
    return m_pImportListView;
}

void BgRmView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    firstShow();
}

void BgRmView::createUi() {
    setObjectName("EP_BGView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    //
    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setObjectName("QLbl_LH24_FS24_FW7");
    auto titleLabLayout = new QHBoxLayout();
    titleLabLayout->setContentsMargins(20, 0, 0, 0);
    titleLabLayout->addWidget(m_pTitleLbl, 0, Qt::AlignLeft);

    //
    m_pImportGuideWidget = new QWidget(this);
    QVBoxLayout *importGuideLayout = new QVBoxLayout(m_pImportGuideWidget);
    importGuideLayout->setContentsMargins(20, 20, 20, 8);
    importGuideLayout->setSpacing(0);

    m_pImportGuide = new ImportGuide(this);

    m_pSmapleWidget = new QWidget(this);
    m_pSmapleWidget->setFixedHeight(100);
    auto smapleWidgetLayout = new QVBoxLayout(m_pSmapleWidget);
    smapleWidgetLayout->setContentsMargins(0, 0, 0, 12);
    smapleWidgetLayout->setSpacing(0);

    m_pSmapleTitleLbl = new QLabel(this);
    m_pSmapleTitleLbl->setObjectName("QLbl_LH20_FS14_FW4");
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
    smapleWidgetLayout->addSpacing(4);
    smapleWidgetLayout->addLayout(sampleImageLayout);

    importGuideLayout->addWidget(m_pImportGuide, 1);
    importGuideLayout->addSpacing(8);
    importGuideLayout->addWidget(m_pSmapleWidget);

    //
    m_pWorkspaceWidget = new QWidget(this);
    auto bodyWidgetLayout = new QHBoxLayout(m_pWorkspaceWidget);
    bodyWidgetLayout->setContentsMargins(0, 0, 0, 0);
    bodyWidgetLayout->setSpacing(0);

    m_pLeftWidget = new QWidget(this);
    auto LeftWidgetLayout = new QVBoxLayout(m_pLeftWidget);
    LeftWidgetLayout->setContentsMargins(12, 12, 0, 10);
    LeftWidgetLayout->setSpacing(0);

    m_pRightWidget = new QWidget(this);
    m_pRightWidget->setFixedWidth(236);
    auto rightWidgetLayout = new QVBoxLayout(m_pRightWidget);
    rightWidgetLayout->setContentsMargins(12, 12, 12, 20);
    rightWidgetLayout->setSpacing(0);

    bodyWidgetLayout->addWidget(m_pLeftWidget, 1);
    bodyWidgetLayout->addWidget(m_pRightWidget);

    //
    m_pImageViewer = new ImageViewer(this);
    m_pImportListView = new ImportListView(this);
    LeftWidgetLayout->addWidget(m_pImageViewer, 1);
    LeftWidgetLayout->addSpacing(8);
    LeftWidgetLayout->addWidget(m_pImportListView);

    //
    m_pBgColorLbl = new QLabel(this);
    m_pBgColorLbl->setObjectName("QLbl_LH16_FS12_FW4");
    rightWidgetLayout->addWidget(m_pBgColorLbl);
    rightWidgetLayout->addSpacing(4);

    m_pBgColor0Btn = new IconButton(this);
    m_pBgColor0Btn->setFixedSize(32, 32);
    m_pBgColor0Btn->setIconSize(32, 32);
    m_pBgColor0Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_alpha.svg").arg(QtmCore::Theme::currentTheme()));

    m_pBgColor1Btn = new IconButton(this);
    m_pBgColor1Btn->setFixedSize(32, 32);
    m_pBgColor1Btn->setIconSize(32, 32);
    m_pBgColor1Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_white.svg").arg(QtmCore::Theme::currentTheme()));

    m_pBgColor2Btn = new IconButton(this);
    m_pBgColor2Btn->setFixedSize(32, 32);
    m_pBgColor2Btn->setIconSize(32, 32);
    m_pBgColor2Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_black.svg").arg(QtmCore::Theme::currentTheme()));

    m_pBgColor3Btn = new IconButton(this);
    m_pBgColor3Btn->setFixedSize(32, 32);
    m_pBgColor3Btn->setIconSize(32, 32);
    m_pBgColor3Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_grey.svg").arg(QtmCore::Theme::currentTheme()));

    m_pBgColor4Btn = new IconButton(this);
    m_pBgColor4Btn->setFixedSize(32, 32);
    m_pBgColor4Btn->setIconSize(32, 32);
    m_pBgColor4Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_light blue.svg").arg(QtmCore::Theme::currentTheme()));

    m_pBgColorSelectBtn = new IconButton(this);
    m_pBgColorSelectBtn->setFixedSize(32, 32);
    m_pBgColorSelectBtn->setIconSize(32, 32);
    m_pBgColorSelectBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_gradiet3.png").arg(QtmCore::Theme::currentTheme()));

    auto bgColorBtnLayout = new QHBoxLayout();
    bgColorBtnLayout->setContentsMargins(0, 0, 0, 0);
    bgColorBtnLayout->setSpacing(4);
    bgColorBtnLayout->addWidget(m_pBgColor0Btn);
    bgColorBtnLayout->addWidget(m_pBgColor1Btn);
    bgColorBtnLayout->addWidget(m_pBgColor2Btn);
    bgColorBtnLayout->addWidget(m_pBgColor3Btn);
    bgColorBtnLayout->addWidget(m_pBgColor4Btn);
    bgColorBtnLayout->addWidget(m_pBgColorSelectBtn);
    bgColorBtnLayout->addStretch();
    rightWidgetLayout->addLayout(bgColorBtnLayout);

    //
    rightWidgetLayout->addSpacing(16);

    //
    m_pBgImgLbl = new QLabel(this);
    m_pBgImgLbl->setObjectName("QLbl_LH16_FS12_FW4");
    rightWidgetLayout->addWidget(m_pBgImgLbl);
    rightWidgetLayout->addSpacing(4);

    m_pBgCustomImgBtn = new QPushButton(this);
    m_pBgCustomImgBtn->setObjectName("QPBtn_H32_R8_B1_T14_W7");
    m_pBgCustomImgBtn->setFixedSize(70, 32);

    m_pBgGeneralImgBtn = new QPushButton(this);
    m_pBgGeneralImgBtn->setObjectName("QPBtn_H32_R8_B1_T14_W7");
    m_pBgGeneralImgBtn->setFixedSize(70, 32);

    m_pBgSceneImgBtn = new QPushButton(this);
    m_pBgSceneImgBtn->setObjectName("QPBtn_H32_R8_B1_T14_W7");
    m_pBgSceneImgBtn->setFixedSize(70, 32);

    auto bgImgBtnLayout = new QHBoxLayout();
    bgImgBtnLayout->setContentsMargins(0, 0, 0, 0);
    bgImgBtnLayout->setSpacing(4);
    bgImgBtnLayout->addWidget(m_pBgCustomImgBtn);
    bgImgBtnLayout->addWidget(m_pBgGeneralImgBtn);
    bgImgBtnLayout->addWidget(m_pBgSceneImgBtn);
    bgImgBtnLayout->addStretch();
    rightWidgetLayout->addLayout(bgImgBtnLayout);

    m_pBgImgListView = new ListView<SBgImgData>(this);
    m_pBgImgListView->setSpacing(0);
    m_pBgImgListDelegate = new BgImgListDelegate(m_pBgImgListView);
    m_pBgImgListView->setItemDelegate(m_pBgImgListDelegate);
    m_pBgImgListView->viewport()->installEventFilter(m_pBgImgListDelegate);
    rightWidgetLayout->addWidget(m_pBgImgListView, 1);
    // m_pBgImgListView->changeData(formatDatas);

    //
    rightWidgetLayout->addSpacing(16);

    //
    m_pOutputFolderLbl = new QLabel(this);
    m_pOutputFolderLbl->setObjectName("QLbl_LH16_FS12_FW4");
    rightWidgetLayout->addWidget(m_pOutputFolderLbl);
    rightWidgetLayout->addSpacing(4);

    m_pOutputFolderCbb = new QComboBox(this);
    m_pOutputFolderCbb->setFixedHeight(24);

    m_pOpenOutputFolderBtn = new IconButton(this);
    m_pOpenOutputFolderBtn->setFixedSize(24, 24);
    m_pOpenOutputFolderBtn->setIconSize(24, 24);
    m_pOpenOutputFolderBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/icon/icon_state/icon24/icon24_file.png").arg(QtmCore::Theme::currentTheme()));

    auto folderLayout = new QHBoxLayout();
    folderLayout->setContentsMargins(0, 0, 0, 0);
    folderLayout->setSpacing(4);
    folderLayout->addWidget(m_pOutputFolderCbb, 1);
    folderLayout->addWidget(m_pOpenOutputFolderBtn);
    rightWidgetLayout->addLayout(folderLayout);

    //
    rightWidgetLayout->addSpacing(16);

    //
    m_pStartAllBtn = new QPushButton(this);
    m_pStartAllBtn->setObjectName("QPBtn_BR16_FS14_FW7");
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

void BgRmView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &BgRmView::onLanguageChange);
    connect(m_pSmaple1ImageLbl, &ClickableLabel::sigClicked, this, &BgRmView::onSmaple1ImageLblClicked);
    connect(m_pSmaple2ImageLbl, &ClickableLabel::sigClicked, this, &BgRmView::onSmaple2ImageLblClicked);
    connect(m_pImportListView, &ImportListView::sigImportListCountChange, this, &BgRmView::onImportListCountChange);
    connect(m_pImportListView, &ImportListView::sigImportListCurrentChanged, this, &BgRmView::onImportListCurrentChanged);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &BgRmView::onGuideImportFile);
    connect(m_pStartAllBtn, &QPushButton::clicked, this, &BgRmView::onStartAllBtnClicked);
    connect(m_pBgCustomImgBtn, &QPushButton::clicked, this, &BgRmView::onBgCustomImgBtnClicked);
    connect(m_pBgGeneralImgBtn, &QPushButton::clicked, this, &BgRmView::onBgGeneralImgBtnClicked);
    connect(m_pBgSceneImgBtn, &QPushButton::clicked, this, &BgRmView::onBgSceneImgBtnClicked);
}

void BgRmView::firstShow() {
    static bool firstShow = true;
    if(firstShow) {
        firstShow = false;
        loadSampleImage();
        initOutputFolderCbbItem();
    }
}

void BgRmView::loadSampleImage() {
    BgRmPresenter *prst = dynamic_cast<BgRmPresenter *>(presenter());
    m_pSmaple1ImageLbl->setPixmap(QPixmap(prst->getSampleImage1Path()).scaled(m_pSmaple1ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pSmaple2ImageLbl->setPixmap(QPixmap(prst->getSampleImage2Path()).scaled(m_pSmaple2ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void BgRmView::importSampleImage1() {
    BgRmPresenter *prst = dynamic_cast<BgRmPresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImage1Path());
    m_pImportListView->importFile(paths);
}

void BgRmView::importSampleImage2() {
    BgRmPresenter *prst = dynamic_cast<BgRmPresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImage2Path());
    m_pImportListView->importFile(paths);
}

void BgRmView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->getBgRmSetting()->getOutPath());
    m_pOutputFolderCbb->addItem("...");
}

void BgRmView::gotoImportGuide() {
    m_pStackedLayout->setCurrentWidget(m_pImportGuideWidget);
}

void BgRmView::gotoWorkspace() {
    m_pStackedLayout->setCurrentWidget(m_pWorkspaceWidget);
}

void BgRmView::imageViewerLoad(const QString &filePath) {
    m_pImageViewer->loadImage(filePath);
}

void BgRmView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Backgroung Remover"));
    m_pSmapleTitleLbl->setText(tr("Try with one of our smaples!"));
    m_pOutputFolderLbl->setText(tr("Output folder"));
    m_pBgColorLbl->setText(tr("Background Color"));
    m_pBgImgLbl->setText(tr("Background Image"));
    m_pBgCustomImgBtn->setText(tr("Custom"));
    m_pBgGeneralImgBtn->setText(tr("General"));
    m_pBgSceneImgBtn->setText(tr("Scene"));
    m_pStartAllBtn->setText(tr("Start"));
}

void BgRmView::onSmaple1ImageLblClicked() {
    importSampleImage1();
}

void BgRmView::onSmaple2ImageLblClicked() {
    importSampleImage2();
}

void BgRmView::onImportListCountChange(int count) {
    if(count > 0) {
        gotoWorkspace();
    } else {
        gotoImportGuide();
    }
}

void BgRmView::onImportListCurrentChanged(const QString filePath) {
    imageViewerLoad(filePath);
}

void BgRmView::onGuideImportFile(const QStringList &filePaths) {
    BgRmPresenter *prst = dynamic_cast<BgRmPresenter *>(presenter());
    m_pImportListView->importFile(filePaths);
}

void BgRmView::onStartAllBtnClicked() {
    BgRmPresenter *prst = dynamic_cast<BgRmPresenter *>(presenter());
    // BgRmTask task;
    // for(auto data : prst->datas()) {
    //     if(data.is_checked) {
    //         task.exec(data.file_path, SETTINGS->conversionOutPath(), SETTINGS->conversionOutFormat());
    //     }
    // }
}

void BgRmView::onBgCustomImgBtnClicked() {
}

void BgRmView::onBgGeneralImgBtnClicked() {
    BgRmPresenter *prst = dynamic_cast<BgRmPresenter *>(presenter());
    QList<SBgImgData> formatDatas = prst->getBgImgDataDatas(EBgImgType_General);
    m_pBgImgListView->changeData(formatDatas);
}

void BgRmView::onBgSceneImgBtnClicked() {
    BgRmPresenter *prst = dynamic_cast<BgRmPresenter *>(presenter());
    QList<SBgImgData> formatDatas = prst->getBgImgDataDatas(EBgImgType_Scene);
    m_pBgImgListView->changeData(formatDatas);
}