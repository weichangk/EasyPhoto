#include "upsc/view.h"
#include "upsc/presenter.h"
#include "settings.h"
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog.h>

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
    importGuideLayout->setContentsMargins(20, 20, 20, 8);
    importGuideLayout->setSpacing(0);

    m_pImportGuide = new ImportGuide(this);

    m_pSmapleWidget = new QWidget(this);
    m_pSmapleWidget->setObjectName("UpscView_m_pSmapleWidget");
    m_pSmapleWidget->setFixedHeight(134);
    auto smapleWidgetLayout = new QVBoxLayout(m_pSmapleWidget);
    smapleWidgetLayout->setContentsMargins(0, 0, 0, 12);
    smapleWidgetLayout->setSpacing(0);

    m_pSmapleTitleLbl = new QLabel(this);
    m_pSmapleTitleLbl->setObjectName("UpscView_m_pSmapleTitleLbl");
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
    m_pRightWidget->setFixedWidth(240 + 24 + 1);
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
    m_pSelectModelLbl = new QLabel(this);
    m_pSelectModelLbl->setObjectName("UpscView_m_pSelectModelLbl");
    m_pSelectModelLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    rightWidgetLayout->addWidget(m_pSelectModelLbl);
    rightWidgetLayout->addSpacing(4);

    //
    m_pSelectModelCbb = new QComboBox(this);
    m_pSelectModelCbb->setFixedHeight(24);
    rightWidgetLayout->addWidget(m_pSelectModelCbb);
    rightWidgetLayout->addSpacing(12);

    //
    m_pModelCard = new ModelCard(this);
    rightWidgetLayout->addWidget(m_pModelCard);
    rightWidgetLayout->addSpacing(12);

    //
    m_pDoubleUpscaleCkb = new QCheckBox(this);

    //
    m_pDoubleUpscaleTipBtn = new IconButton(this);
    m_pDoubleUpscaleTipBtn->setFixedSize(16, 16);
    m_pDoubleUpscaleTipBtn->setIconSize(16, 16);
    m_pDoubleUpscaleTipBtn->setFourPixmapPath(":/QtmImg/img/dark/v16/icon16/icon20_question mark.svg");

    //
    auto doubleUpscaleLayout = new QHBoxLayout();
    doubleUpscaleLayout->setContentsMargins(0, 0, 0, 0);
    doubleUpscaleLayout->setSpacing(4);
    doubleUpscaleLayout->addWidget(m_pDoubleUpscaleCkb);
    doubleUpscaleLayout->addWidget(m_pDoubleUpscaleTipBtn);
    doubleUpscaleLayout->addStretch();
    m_pDoubleUpscaleCkb->setVisible(false);
    m_pDoubleUpscaleTipBtn->setVisible(false);

    //
    rightWidgetLayout->addLayout(doubleUpscaleLayout);
    rightWidgetLayout->addSpacing(12);

    //
    m_pScaleLbl = new QLabel(this);
    m_pScaleLbl->setObjectName("UpscView_m_pScaleLbl");
    m_pScaleLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    rightWidgetLayout->addWidget(m_pScaleLbl);
    rightWidgetLayout->addSpacing(4);

    //
    m_pScaleCbb = new QComboBox(this);
    m_pScaleCbb->setFixedHeight(24);
    rightWidgetLayout->addWidget(m_pScaleCbb);
    rightWidgetLayout->addSpacing(12);

    //
    m_pSaveAsFormatLbl = new QLabel(this);
    m_pSaveAsFormatLbl->setObjectName("UpscView_m_pSaveAsFormatLbl");
    rightWidgetLayout->addWidget(m_pSaveAsFormatLbl);
    rightWidgetLayout->addSpacing(4);

    //
    m_pSaveAsFormatCbb = new QComboBox(this);
    m_pSaveAsFormatCbb->setFixedHeight(24);
    rightWidgetLayout->addWidget(m_pSaveAsFormatCbb);
    rightWidgetLayout->addSpacing(12);

    //
    m_pOutputFolderLbl = new QLabel(this);
    m_pOutputFolderLbl->setObjectName("UpscView_m_pOutputFolderLbl");
    rightWidgetLayout->addWidget(m_pOutputFolderLbl);
    rightWidgetLayout->addSpacing(4);

    //
    m_pOutputFolderCbb = new QComboBox(this);
    m_pOutputFolderCbb->setFixedHeight(24);

    //
    m_pOpenOutputFolderBtn = new IconButton(this);
    m_pOpenOutputFolderBtn->setFixedSize(24, 24);
    m_pOpenOutputFolderBtn->setIconSize(24, 24);
    m_pOpenOutputFolderBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_file.png");

    //
    auto outputFolderLayout = new QHBoxLayout();
    outputFolderLayout->setContentsMargins(0, 0, 0, 0);
    outputFolderLayout->setSpacing(4);
    outputFolderLayout->addWidget(m_pOutputFolderCbb, 1);
    outputFolderLayout->addWidget(m_pOpenOutputFolderBtn);

    //
    rightWidgetLayout->addLayout(outputFolderLayout);
    rightWidgetLayout->addSpacing(12);

    //
    rightWidgetLayout->addStretch();

    //
    m_pExportBtn = new QPushButton(this);
    m_pExportBtn->setObjectName("UpscView_m_pExportBtn");
    m_pExportBtn->setFixedHeight(32);
    rightWidgetLayout->addWidget(m_pExportBtn);

    //
    m_pStackedLayout = new QStackedLayout();
    m_pStackedLayout->addWidget(m_pImportGuideWidget);
    m_pStackedLayout->addWidget(m_pWorkspaceWidget);

    //
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
    connect(m_pExportBtn, &QPushButton::clicked, this, &UpscView::onExportBtnClicked);
    connect(m_pSelectModelCbb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &UpscView::onSelectModelCbbCurrentIndex);
    connect(m_pScaleCbb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &UpscView::onScaleCbbCurrentIndex);
    connect(m_pSaveAsFormatCbb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &UpscView::onSaveAsFormatCbbCurrentIndex);
    connect(m_pDoubleUpscaleCkb, &QCheckBox::stateChanged, this, &UpscView::onDoubleUpscaleCkbStateChanged);
    connect(m_pOpenOutputFolderBtn, &QPushButton::clicked, this, &UpscView::onOpenOutputFolderBtnClicked);
    connect(m_pOutputFolderCbb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &UpscView::onOutputFolderCbbIndexChanged);
}

void UpscView::firstShow() {
    static bool firstShow = true;
    if(firstShow) {
        firstShow = false;
        loadSampleImage();
        initSelectModelCbbItem();
        initModelCard();
        initOutputFolderCbbItem();
        initUpscaleCbbItem();
        initDoubleUpscaleCkb();
        initSaveAsFormatCbbItem();
    }
}

void UpscView::loadSampleImage() {
    UpscPresenter *prst = dynamic_cast<UpscPresenter *>(presenter());
    m_pStandardSmapleImageLbl->setPixmap(QPixmap(prst->getSampleBeforeImagePath(EUpscModelType_Standard)).scaled(m_pStandardSmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pLiteSmapleImageLbl->setPixmap(QPixmap(prst->getSampleBeforeImagePath(EUpscModelType_Lite)).scaled(m_pLiteSmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pFidelitySmapleImageLbl->setPixmap(QPixmap(prst->getSampleBeforeImagePath(EUpscModelType_Fidelity)).scaled(m_pFidelitySmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pRemacriSmapleImageLbl->setPixmap(QPixmap(prst->getSampleBeforeImagePath(EUpscModelType_Remacri)).scaled(m_pRemacriSmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pUltramixSmapleImageLbl->setPixmap(QPixmap(prst->getSampleBeforeImagePath(EUpscModelType_Ultramix)).scaled(m_pUltramixSmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pUltrasharpSmapleImageLbl->setPixmap(QPixmap(prst->getSampleBeforeImagePath(EUpscModelType_Ultrasharp)).scaled(m_pUltrasharpSmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pDigitalSmapleImageLbl->setPixmap(QPixmap(prst->getSampleBeforeImagePath(EUpscModelType_Digital)).scaled(m_pDigitalSmapleImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void UpscView::importSampleImage(EUpscModelType type) {
    UpscPresenter *prst = dynamic_cast<UpscPresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleBeforeImagePath(type));
    m_pImportListView->importFile(paths);
    m_pSelectModelCbb->setCurrentIndex(type);
}

void UpscView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->getUpscSetting()->getOutPath());
    m_pOutputFolderCbb->addItem("...");
}

void UpscView::initSelectModelCbbItem() {
    blockSignalsFunc(m_pSelectModelCbb, [&]() {
        m_pSelectModelCbb->clear();
        m_pSelectModelCbb->addItems(UPSC_MODEL_TITLES.values());
        m_pSelectModelCbb->setCurrentIndex(SETTINGS->getUpscSetting()->getModelType());
    });
}

void UpscView::initModelCard() {
    int type = SETTINGS->getUpscSetting()->getModelType();
    UpscPresenter *prst = dynamic_cast<UpscPresenter *>(presenter());
    auto modelDatas = prst->getSelectModelDatas();
    auto it = std::find_if(modelDatas.begin(), modelDatas.end(),
                           [type](const SUpscSelectModelData &data) {
                               return static_cast<int>(data.type) == type;
                           });
    if (it == modelDatas.end())
        return;
    const SUpscSelectModelData &model = *it;
    m_pModelCard->setInfo(model.title, model.desc, model.beforeThumb, model.afterThumb);
}

void UpscView::initUpscaleCbbItem() {
    blockSignalsFunc(m_pScaleCbb, [&]() {
        m_pScaleCbb->clear();
        m_pScaleCbb->addItems(UPSC_SCALES.values());
        m_pScaleCbb->setCurrentIndex(UPSC_SCALES.keys().indexOf(SETTINGS->getUpscSetting()->getScale()));
    });
}

void UpscView::initDoubleUpscaleCkb() {
    blockSignalsFunc(m_pDoubleUpscaleCkb, [&]() {
        m_pDoubleUpscaleCkb->setChecked(SETTINGS->getUpscSetting()->getDoubleUpscale());
    });
}

void UpscView::initSaveAsFormatCbbItem() {
    blockSignalsFunc(m_pSaveAsFormatCbb, [&]() {
        m_pSaveAsFormatCbb->clear();
        m_pSaveAsFormatCbb->addItems(UPSC_OUTPUT_FORMATS.values());
        m_pSaveAsFormatCbb->setCurrentIndex(UPSC_OUTPUT_FORMATS.keys().indexOf(SETTINGS->getUpscSetting()->getOutFmt()));
    });
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

void UpscView::setOutputFolder(const QString &path) {
    SETTINGS->getUpscSetting()->setOutPath(path);
    m_pOutputFolderCbb->setItemText(0, path);
}

void UpscView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Ai Image Enhancer"));
    m_pSmapleTitleLbl->setText(tr("Try with one of our smaples!"));
    m_pSelectModelLbl->setText(tr("Select AI Model"));
    m_pDoubleUpscaleCkb->setText(tr("Double Upscayl"));
    m_pScaleLbl->setText(tr("Image Scale"));
    m_pSaveAsFormatLbl->setText(tr("Save As Format"));
    m_pOutputFolderLbl->setText(tr("Save Output Folder"));
    m_pExportBtn->setText(tr("Upscayl"));
}

void UpscView::onStandardSmapleImageLblClicked() {
    importSampleImage(EUpscModelType_Standard);
}

void UpscView::onLiteSmapleImageLblClicked() {
    importSampleImage(EUpscModelType_Lite);
}

void UpscView::onFidelitySmapleImageLblClicked() {
    importSampleImage(EUpscModelType_Fidelity);
}

void UpscView::onRemacriSmapleImageLblClicked() {
    importSampleImage(EUpscModelType_Remacri);
}

void UpscView::onUltramixSmapleImageLblClicked() {
    importSampleImage(EUpscModelType_Ultramix);
}

void UpscView::onUltrasharpSmapleImageLblClicked() {
    importSampleImage(EUpscModelType_Ultrasharp);
}

void UpscView::onDigitalSmapleImageLblClicked() {
    importSampleImage(EUpscModelType_Digital);
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

void UpscView::onExportBtnClicked() {
    UpscPresenter *prst = dynamic_cast<UpscPresenter *>(presenter());
    prst->Upsc();
}

void UpscView::onSelectModelCbbCurrentIndex(int index) {
    SETTINGS->getUpscSetting()->setModelType(index);
    initModelCard();
}

void UpscView::onScaleCbbCurrentIndex(int index) {
    SETTINGS->getUpscSetting()->setScale(UPSC_SCALES.keys()[index]);
}

void UpscView::onSaveAsFormatCbbCurrentIndex(int index) {
    SETTINGS->getUpscSetting()->setOutFmt(UPSC_OUTPUT_FORMATS.keys()[index]);
}

void UpscView::onDoubleUpscaleCkbStateChanged(int state) {
    SETTINGS->getUpscSetting()->setDoubleUpscale(m_pDoubleUpscaleCkb->isChecked());
}

void UpscView::onOpenOutputFolderBtnClicked() {
    QString folderPath = SETTINGS->getUpscSetting()->getOutPath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
}

void UpscView::onOutputFolderCbbIndexChanged(int index) {
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