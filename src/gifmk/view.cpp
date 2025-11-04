#include "gifmk/view.h"
#include "gifmk/presenter.h"
#include "gifmk/task.h"
#include "core/theme.h"
#include "settings.h"
#include "message/funcchangemessage.h"
#include "funcenum.h"
#include "types.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QButtonGroup>

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
}

void GifMkView::createUi() {
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
    m_pImageViewer = new ImageWorkWidget(this);
    m_pImportListView = new ImportListView(this);
    LeftWidgetLayout->addWidget(m_pImageViewer, 1);
    LeftWidgetLayout->addSpacing(8);
    LeftWidgetLayout->addWidget(m_pImportListView);

    //
    auto scaleOrSizeBtnWidget = new QWidget();
    scaleOrSizeBtnWidget->setObjectName("EP_SwitchBtnWidget");
    scaleOrSizeBtnWidget->setFixedHeight(28);

    auto scaleOrSizeBtnLayout = new QHBoxLayout(scaleOrSizeBtnWidget);
    scaleOrSizeBtnLayout->setContentsMargins(2, 2, 2, 2);
    scaleOrSizeBtnLayout->setSpacing(4);

    m_pSizeBtn = new QPushButton(this);
    m_pSizeBtn->setObjectName("EP_SwitchBtn");
    m_pSizeBtn->setFixedHeight(24);
    m_pSizeBtn->setCheckable(true);
    scaleOrSizeBtnLayout->addWidget(m_pSizeBtn);

    m_pScaleBtn = new QPushButton(this);
    m_pScaleBtn->setObjectName("EP_SwitchBtn");
    m_pScaleBtn->setFixedHeight(24);
    m_pScaleBtn->setCheckable(true);
    scaleOrSizeBtnLayout->addWidget(m_pScaleBtn);

    auto scaleOrSizeBtnGroup = new QButtonGroup(this);
    scaleOrSizeBtnGroup->setExclusive(true);
    scaleOrSizeBtnGroup->addButton(m_pSizeBtn, 0);
    scaleOrSizeBtnGroup->addButton(m_pScaleBtn, 1);
    m_pSizeBtn->setChecked(true);

    rightWidgetLayout->addWidget(scaleOrSizeBtnWidget);
    rightWidgetLayout->addSpacing(4);

    //
    m_pPixelsWidthLdt = new UnitLineEdit(this);
    m_pPixelsWidthLdt->setFixedHeight(24);
    m_pPixelsWidthLdt->setAlignment(Qt::AlignCenter);
    m_pPixelsWidthLdt->setPrefix("W");
    m_pPixelsWidthLdt->setUnit("PX");
    m_pPixelsWidthLdt->setText("0");
    m_pPixelsHeightLdt = new UnitLineEdit(this);
    m_pPixelsHeightLdt->setFixedHeight(24);
    m_pPixelsHeightLdt->setAlignment(Qt::AlignCenter);
    m_pPixelsHeightLdt->setPrefix("H");
    m_pPixelsHeightLdt->setUnit("PX");
    m_pPixelsHeightLdt->setText("0");
    m_pLockScaleBtn = new IconButton(this);
    m_pLockScaleBtn->setFixedSize(24, 24);
    m_pLockScaleBtn->setIconSize(24, 24);
    m_pLockScaleBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    m_pLockScaleBtn->setCheckable(true);
    m_pLockScaleBtn->setChecked(true);

    auto pixelsLayout = new QHBoxLayout();
    pixelsLayout->setContentsMargins(0, 0, 0, 0);
    pixelsLayout->setSpacing(4);
    pixelsLayout->addWidget(m_pPixelsWidthLdt, 1);
    pixelsLayout->addWidget(m_pLockScaleBtn);
    pixelsLayout->addWidget(m_pPixelsHeightLdt, 1);
    rightWidgetLayout->addLayout(pixelsLayout);
    rightWidgetLayout->addSpacing(4);

    m_pSizeCbb = new QComboBox(this);
    m_pSizeCbb->setFixedHeight(24);
    rightWidgetLayout->addWidget(m_pSizeCbb);

    m_pScaleCbb = new QComboBox(this);
    m_pScaleCbb->setFixedHeight(24);
    rightWidgetLayout->addWidget(m_pScaleCbb);
    m_pScaleCbb->setVisible(false);

    rightWidgetLayout->addSpacing(16);

    //
    m_pPlayLbl = new QLabel(this);
    m_pPlayLbl->setObjectName("QLbl_LH16_FS12_FW4");
    rightWidgetLayout->addWidget(m_pPlayLbl);
    rightWidgetLayout->addSpacing(4);

    m_pLoopCkb = new QCheckBox(this);
    m_pReverseCkb = new QCheckBox(this);

    auto playLayout = new QHBoxLayout();
    playLayout->setContentsMargins(0, 0, 0, 0);
    playLayout->setSpacing(8);
    playLayout->addWidget(m_pLoopCkb);
    playLayout->addWidget(m_pReverseCkb);
    playLayout->addStretch();
    rightWidgetLayout->addLayout(playLayout);

    rightWidgetLayout->addSpacing(16);

    //
    m_pSpeedLbl = new QLabel(this);
    m_pSpeedLbl->setObjectName("QLbl_LH16_FS12_FW4");
    m_pSpeedDescLbl = new QLabel(this);
    m_pSpeedDescLbl->setObjectName("QLbl_LH16_FS12_FW4");
    auto speedLblLayout = new QHBoxLayout();
    speedLblLayout->setContentsMargins(0, 0, 0, 0);
    speedLblLayout->setSpacing(8);
    speedLblLayout->addWidget(m_pSpeedLbl);
    speedLblLayout->addWidget(m_pSpeedDescLbl);
    speedLblLayout->addStretch();
    rightWidgetLayout->addLayout(speedLblLayout);

    m_pSpeedSlider = new QSlider(Qt::Horizontal, this);
    m_pSpeedSlider->setRange(1, 60);
    m_pSpeedSlider->setPageStep(1);
    rightWidgetLayout->addWidget(m_pSpeedSlider);

    rightWidgetLayout->addSpacing(16);

    //
    m_pBgLbl = new QLabel(this);
    m_pBgLbl->setObjectName("QLbl_LH16_FS12_FW4");
    rightWidgetLayout->addWidget(m_pBgLbl);
    rightWidgetLayout->addSpacing(4);

    m_pBg1Btn = new IconButton(this);
    m_pBg1Btn->setFixedSize(32, 32);
    m_pBg1Btn->setIconSize(32, 32);
    m_pBg1Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_alpha.svg").arg(QtmCore::Theme::currentTheme()), true);
    m_pBg1Btn->setCheckable(true);

    m_pBg2Btn = new IconButton(this);
    m_pBg2Btn->setFixedSize(32, 32);
    m_pBg2Btn->setIconSize(32, 32);
    m_pBg2Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_white.svg").arg(QtmCore::Theme::currentTheme()));
    m_pBg2Btn->setCheckable(true);

    m_pBg3Btn = new IconButton(this);
    m_pBg3Btn->setFixedSize(32, 32);
    m_pBg3Btn->setIconSize(32, 32);
    m_pBg3Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_black.svg").arg(QtmCore::Theme::currentTheme()));
    m_pBg3Btn->setCheckable(true);

    m_pBg4Btn = new IconButton(this);
    m_pBg4Btn->setFixedSize(32, 32);
    m_pBg4Btn->setIconSize(32, 32);
    m_pBg4Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_grey.svg").arg(QtmCore::Theme::currentTheme()));
    m_pBg4Btn->setCheckable(true);

    m_pBg5Btn = new IconButton(this);
    m_pBg5Btn->setFixedSize(32, 32);
    m_pBg5Btn->setIconSize(32, 32);
    m_pBg5Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_light blue.svg").arg(QtmCore::Theme::currentTheme()));
    m_pBg5Btn->setCheckable(true);

    m_pBgSelectBtn = new IconButton(this);
    m_pBgSelectBtn->setFixedSize(32, 32);
    m_pBgSelectBtn->setIconSize(32, 32);
    m_pBgSelectBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_gradiet3.png").arg(QtmCore::Theme::currentTheme()));

    m_pBgBtnGroup = new QButtonGroup(this);
    m_pBgBtnGroup->setExclusive(true);
    m_pBgBtnGroup->addButton(m_pBg1Btn, 0);
    m_pBgBtnGroup->addButton(m_pBg2Btn, 1);
    m_pBgBtnGroup->addButton(m_pBg3Btn, 2);
    m_pBgBtnGroup->addButton(m_pBg4Btn, 3);
    m_pBgBtnGroup->addButton(m_pBg5Btn, 4);

    auto bgBtnLayout = new QHBoxLayout();
    bgBtnLayout->setContentsMargins(0, 0, 0, 0);
    bgBtnLayout->setSpacing(4);
    bgBtnLayout->addWidget(m_pBg1Btn);
    bgBtnLayout->addWidget(m_pBg2Btn);
    bgBtnLayout->addWidget(m_pBg3Btn);
    bgBtnLayout->addWidget(m_pBg4Btn);
    bgBtnLayout->addWidget(m_pBg5Btn);
    bgBtnLayout->addWidget(m_pBgSelectBtn);
    rightWidgetLayout->addLayout(bgBtnLayout);

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
    folderLayout->addWidget(m_pOutputFolderCbb, 1);
    folderLayout->addWidget(m_pOpenOutputFolderBtn);
    rightWidgetLayout->addLayout(folderLayout);

    rightWidgetLayout->addStretch();

    //
    m_pPreviewBtn = new QPushButton(this);
    m_pPreviewBtn->setObjectName("QPBtn_BR16_FS14_FW7");
    m_pPreviewBtn->setFixedHeight(32);
    rightWidgetLayout->addWidget(m_pPreviewBtn);

    rightWidgetLayout->addSpacing(8);

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

void GifMkView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &GifMkView::onLanguageChange);
    connect(m_pOutputFolderCbb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &GifMkView::onOutputFolderCbbIndexChanged);
    connect(m_pOpenOutputFolderBtn, &QPushButton::clicked, this, &GifMkView::onOpenOutputFolderBtnClicked);
    connect(m_pPreviewBtn, &QPushButton::clicked, this, &GifMkView::onPreviewBtnClicked);
    connect(m_pStartAllBtn, &QPushButton::clicked, this, &GifMkView::onStartAllClicked);
    connect(m_pImportListView, &ImportListView::sigImportListCountChange, this, &GifMkView::onImportListCountChange);
    connect(m_pImportListView, &ImportListView::sigImportListCurrentChanged, this, &GifMkView::onImportListCurrentChanged);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &GifMkView::onGuideImportFile);

    connect(m_pSizeBtn, &QPushButton::clicked, this, &GifMkView::onSizeBtnClicked);
    connect(m_pScaleBtn, &QPushButton::clicked, this, &GifMkView::onScaleBtnClicked);
    connect(m_pScaleCbb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &GifMkView::onScaleCbbIndexChanged);
    connect(m_pSizeCbb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &GifMkView::onSizeCbbIndexChanged);
    connect(m_pLockScaleBtn, &QPushButton::clicked, this, &GifMkView::onLockScaleBtnClicked);
    connect(m_pLoopCkb, &QCheckBox::stateChanged, this, &GifMkView::onLoopCkbStateChanged);
    connect(m_pReverseCkb, &QCheckBox::stateChanged, this, &GifMkView::onReverseCkbStateChanged);
    connect(m_pSpeedSlider, &QSlider::valueChanged, this, &GifMkView::onSpeedSliderValueChanged);
    connect(m_pBg1Btn, &QPushButton::clicked, this, &GifMkView::onBg1BtnClicked);
    connect(m_pBg2Btn, &QPushButton::clicked, this, &GifMkView::onBg2BtnClicked);
    connect(m_pBg3Btn, &QPushButton::clicked, this, &GifMkView::onBg3BtnClicked);
    connect(m_pBg4Btn, &QPushButton::clicked, this, &GifMkView::onBg4BtnClicked);
    connect(m_pBg5Btn, &QPushButton::clicked, this, &GifMkView::onBg5BtnClicked);
    connect(m_pBgSelectBtn, &QPushButton::clicked, this, &GifMkView::onBgSelectBtnClicked);
}

void GifMkView::firstShow() {
    static bool firstShow = true;
    if (firstShow) {
        firstShow = false;
        initUI();
        initOutputFolderCbbItem();
    }
}

QWidget *GifMkView::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("EP_Line");
    dividingLine->setFixedHeight(1);
    return dividingLine;
}

void GifMkView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->getGifMkSetting()->getOutPath());
    m_pOutputFolderCbb->addItem("...");
}

void GifMkView::setOutputFolder(const QString &path) {
    SETTINGS->getGifMkSetting()->setOutPath(path);
    m_pOutputFolderCbb->setItemText(0, path);
}

void GifMkView::initUI() {
    blockSignalsFunc(m_pScaleCbb, [&]() {
        m_pScaleCbb->clear();
        m_pScaleCbb->addItems(GIFMK_SCALES.keys());
    });

    blockSignalsFunc(m_pSizeCbb, [&]() {
        m_pSizeCbb->clear();
        m_pSizeCbb->addItems(GIFMK_SIZES.keys());
    });

    blockSignalsFunc(m_pLoopCkb, [&]() {
        m_pLoopCkb->setChecked(SETTINGS->getGifMkSetting()->getRepeat());
    });

    blockSignalsFunc(m_pReverseCkb, [&]() {
        m_pReverseCkb->setChecked(SETTINGS->getGifMkSetting()->getReverse());
    });

    blockSignalsFunc(m_pSpeedSlider, [&]() {
        m_pSpeedSlider->setValue(SETTINGS->getGifMkSetting()->getFps());
        m_pSpeedDescLbl->setText(tr("(%1 frame / s)").arg(m_pSpeedSlider->value()));
    });
}

void GifMkView::gotoImportGuide() {
    m_pStackedLayout->setCurrentWidget(m_pImportGuideWidget);
}

void GifMkView::gotoWorkspace() {
    m_pStackedLayout->setCurrentWidget(m_pWorkspaceWidget);
}

void GifMkView::imageViewerLoad(const QString &filePath) {
    m_pImageViewer->workspace()->loadImage(filePath);
    m_pImageViewer->workspace()->setFitView();
}

void GifMkView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Gif Maker"));
    m_pScaleBtn->setText(tr("Scale"));
    m_pSizeBtn->setText(tr("Size"));
    m_pPlayLbl->setText(tr("Play"));
    m_pLoopCkb->setText(tr("Loop"));
    m_pReverseCkb->setText(tr("Reverse"));
    m_pSpeedLbl->setText(tr("Speed"));
    m_pSpeedDescLbl->setText(tr("(1.0s / frame)"));
    m_pBgLbl->setText(tr("Background"));
    m_pOutputFolderLbl->setText(tr("Output folder"));
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
    QString folderPath = SETTINGS->getGifMkSetting()->getOutPath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
}

void GifMkView::onPreviewBtnClicked() {
}

void GifMkView::onStartAllClicked() {
    GifMkPresenter *prst = dynamic_cast<GifMkPresenter *>(presenter());
    EasyPhotoCore::GifMk::Task task;
    QList<QString> filePaths;
    for (auto data : prst->getDatas()) {
        filePaths.append(data.file_path);
    }
    EasyPhotoCore::GifMk::SParam param = {
        filePaths,
        SETTINGS->getGifMkSetting()->getWidth(),
        SETTINGS->getGifMkSetting()->getHeight(),
        SETTINGS->getGifMkSetting()->getQuality(),
        SETTINGS->getGifMkSetting()->getFps(),
        SETTINGS->getGifMkSetting()->getRepeat(),
        SETTINGS->getGifMkSetting()->getOutPath(),
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

void GifMkView::onSizeBtnClicked() {
    m_pSizeBtn->setChecked(true);
    m_pPixelsWidthLdt->setEnabled(true);
    m_pPixelsHeightLdt->setEnabled(true);
    m_pSizeCbb->setVisible(true);
    m_pScaleCbb->setVisible(false);
}

void GifMkView::onScaleBtnClicked() {
    m_pScaleBtn->setChecked(true);
    m_pPixelsWidthLdt->setEnabled(false);
    m_pPixelsHeightLdt->setEnabled(false);
    m_pSizeCbb->setVisible(false);
    m_pScaleCbb->setVisible(true);
}

void GifMkView::onScaleCbbIndexChanged(int index) {
    // QString scaleText = m_pScaleCbb->currentText();
    // if (GIFMK_SCALES.contains(scaleText)) {
    //     double scale = GIFMK_SCALES.value(scaleText);
    //     GifMkPresenter *prst = dynamic_cast<GifMkPresenter *>(presenter());
    //     QSize size = prst->getOriginalSize();
    //     int newWidth = static_cast<int>(size.width() * scale);
    //     int newHeight = static_cast<int>(size.height() * scale);
    //     blockSignalsFunc(m_pPixelsWidthLdt, [&]() {
    //         m_pPixelsWidthLdt->setText(QString::number(newWidth));
    //     });
    //     blockSignalsFunc(m_pPixelsHeightLdt, [&]() {
    //         m_pPixelsHeightLdt->setText(QString::number(newHeight));
    //     });
    // }
}

void GifMkView::onSizeCbbIndexChanged(int index) {
    // QString sizeText = m_pSizeCbb->currentText();
    // if (GIFMK_SIZES.contains(sizeText)) {
    //     QSize size = GIFMK_SIZES.value(sizeText);
    //     blockSignalsFunc(m_pPixelsWidthLdt, [&]() {
    //         m_pPixelsWidthLdt->setText(QString::number(size.width()));
    //     });
    //     blockSignalsFunc(m_pPixelsHeightLdt, [&]() {
    //         m_pPixelsHeightLdt->setText(QString::number(size.height()));
    //     });
    // }
}   

void GifMkView::onLockScaleBtnClicked() {
    m_pLockScaleBtn->setChecked(!m_pLockScaleBtn->isChecked());
    m_pLockScaleBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/%2.svg").arg(QtmCore::Theme::currentTheme()).arg(m_pLockScaleBtn->isChecked() ? "icon24_lock" : "icon24_unlock"));
}

void GifMkView::onLoopCkbStateChanged(int state) {
    SETTINGS->getGifMkSetting()->setRepeat(state == Qt::Checked);
}

void GifMkView::onReverseCkbStateChanged(int state) {
    SETTINGS->getGifMkSetting()->setReverse(state == Qt::Checked);
}

void GifMkView::onSpeedSliderValueChanged(int value) {
    SETTINGS->getGifMkSetting()->setFps(value);
    m_pSpeedDescLbl->setText(tr("(%1 frame / s)").arg(value));
}

void GifMkView::onBg1BtnClicked() {
    SETTINGS->getGifMkSetting()->setBgColor("transparent");
}

void GifMkView::onBg2BtnClicked() {
    SETTINGS->getGifMkSetting()->setBgColor("#ffffff");
}

void GifMkView::onBg3BtnClicked() {
    SETTINGS->getGifMkSetting()->setBgColor("#000000");
}

void GifMkView::onBg4BtnClicked() {
    SETTINGS->getGifMkSetting()->setBgColor("#cccccc");
}

void GifMkView::onBg5BtnClicked() {
    SETTINGS->getGifMkSetting()->setBgColor("#8cd6fe");
}

void GifMkView::onBgSelectBtnClicked() {
    QString title = tr("Select Color");
    QString dirPath = QFileDialog::getOpenFileName(this, title, QDir::homePath(), tr("Images (*.png *.jpg *.bmp);;All Files (*)"));
    if (!dirPath.isEmpty()) {
        SETTINGS->getGifMkSetting()->setBgColor(dirPath);
    }
}