#include "bgremover/view.h"
#include "bgremover/presenter.h"
#include "settings.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>

BackgroungRemoverView::BackgroungRemoverView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

void BackgroungRemoverView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    firstShow();
}

void BackgroungRemoverView::createUi() {
    setObjectName("BackgroungRemoverView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setObjectName("BackgroungRemoverView_m_pTitleLbl");
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
    m_pAddFileBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/icon/icon_state/icon32/icon32_add_file.png");

    m_pAddFolderBtn = new IconButton(topWidget);
    m_pAddFolderBtn->setFixedSize(32, 32);
    m_pAddFolderBtn->setIconSize(32, 32);
    m_pAddFolderBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/icon/icon_state/icon32/icon32_add_folder.png");

    m_pClearFileBtn = new IconButton(topWidget);
    m_pClearFileBtn->setFixedSize(24, 24);
    m_pClearFileBtn->setIconSize(24, 24);
    m_pClearFileBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/icon/icon_state/icon24/icon24_delete.png");

    m_pSelectAllCkb = new QCheckBox(topWidget);
    m_pSelectAllCkb->setObjectName("BackgroungRemoverView_m_pSelectAllCkb");

    m_pListModeSwitchBtn = new IconButton(topWidget);
    m_pListModeSwitchBtn->setFixedSize(24, 24);
    m_pListModeSwitchBtn->setIconSize(24, 24);
    m_pListModeSwitchBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/icon/icon_state/icon24/icon24_thumbnail.png");

    auto topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setContentsMargins(20, 0, 20, 0);
    topWidgetLayout->setSpacing(12);
    topWidgetLayout->addWidget(m_pAddFileBtn);
    topWidgetLayout->addWidget(m_pAddFolderBtn);
    topWidgetLayout->addStretch();
    topWidgetLayout->addWidget(m_pSelectAllCkb);
    topWidgetLayout->addWidget(m_pClearFileBtn);
    topWidgetLayout->addWidget(m_pListModeSwitchBtn);

    QWidget *bottomWidget = new QWidget(this);
    bottomWidget->setFixedHeight(70);

    m_pOutputFolderLbl = new QLabel(bottomWidget);
    m_pOutputFolderLbl->setObjectName("BackgroungRemoverView_m_pOutputFolderLbl");

    m_pOutputFolderCbb = new QComboBox(bottomWidget);
    m_pOutputFolderCbb->setFixedSize(240, 24);

    m_pOutputFolderCbbFilter = new ComboBoxFilter(m_pOutputFolderCbb);
    m_pOutputFolderCbb->installEventFilter(m_pOutputFolderCbbFilter);

    m_pOpenOutputFolderBtn = new IconButton(bottomWidget);
    m_pOpenOutputFolderBtn->setFixedSize(24, 24);
    m_pOpenOutputFolderBtn->setIconSize(24, 24);
    m_pOpenOutputFolderBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/icon/icon_state/icon24/icon24_file.png");

    m_pStartAllBtn = new QPushButton(bottomWidget);
    m_pStartAllBtn->setObjectName("BackgroungRemoverView_m_pStartAllBtn");
    m_pStartAllBtn->setFixedSize(110, 32);

    auto bottomWidgetLayout = new QHBoxLayout(bottomWidget);
    bottomWidgetLayout->setContentsMargins(20, 0, 20, 0);
    bottomWidgetLayout->setSpacing(0);
    bottomWidgetLayout->addWidget(m_pOutputFolderLbl);
    bottomWidgetLayout->addSpacing(4);
    bottomWidgetLayout->addWidget(m_pOutputFolderCbb);
    bottomWidgetLayout->addSpacing(4);
    bottomWidgetLayout->addWidget(m_pOpenOutputFolderBtn);
    bottomWidgetLayout->addStretch();
    bottomWidgetLayout->addWidget(m_pStartAllBtn);

    m_pListView = new ListView<SBGRemoverData>(this);
    m_pListView->setSpacing(0);
    m_pListDelegate = new BackgroungRemoverListDelegate(m_pListView);
    m_pListView->setItemDelegate(m_pListDelegate);
    m_pListView->viewport()->installEventFilter(m_pListDelegate);
    auto listViewLayout = new QVBoxLayout();
    listViewLayout->setContentsMargins(20, 0, 2, 0);
    listViewLayout->setSpacing(0);
    listViewLayout->addWidget(m_pListView, 1);

    m_pWorkspaceWidget = new QWidget(this);
    auto workspaceWidgetLayout = new QVBoxLayout(m_pWorkspaceWidget);
    workspaceWidgetLayout->setContentsMargins(0, 0, 0, 0);
    workspaceWidgetLayout->setSpacing(0);
    workspaceWidgetLayout->addWidget(topWidget);
    workspaceWidgetLayout->addLayout(listViewLayout, 1);
    workspaceWidgetLayout->addWidget(createDividingLine());
    workspaceWidgetLayout->addWidget(bottomWidget);

    m_pStackedLayout = new QStackedLayout();
    m_pStackedLayout->addWidget(m_pImportGuideWidget);
    m_pStackedLayout->addWidget(m_pWorkspaceWidget);

    auto stackedMarginLayout = new QVBoxLayout();
    stackedMarginLayout->setContentsMargins(0, 0, 0, 0);
    stackedMarginLayout->addLayout(m_pStackedLayout, 1);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(titleLabLayout, 0);
    layout->addLayout(stackedMarginLayout, 1);
}

void BackgroungRemoverView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &BackgroungRemoverView::onLanguageChange);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &BackgroungRemoverView::listViewImportFile);
    connect(m_pAddFileBtn, &QPushButton::clicked, this, &BackgroungRemoverView::onAddFileBtnClicked);
    connect(m_pAddFolderBtn, &QPushButton::clicked, this, &BackgroungRemoverView::onAddFolderBtnClicked);
    connect(m_pClearFileBtn, &QPushButton::clicked, this, &BackgroungRemoverView::onClearFileBtnClicked);
    connect(m_pSelectAllCkb, &QCheckBox::stateChanged, this, &BackgroungRemoverView::onSelectAllStateChanged);
    connect(m_pListModeSwitchBtn, &QPushButton::clicked, this, &BackgroungRemoverView::onListModeSwitchBtnClicked);
    connect(m_pListView, &QListView::clicked, this, &BackgroungRemoverView::onListViewClicked);
    connect(m_pOutputFolderCbbFilter, &ComboBoxFilter::sigClicked, this, &BackgroungRemoverView::onOutputFolderCbbClicked);
    connect(m_pOutputFolderCbb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &BackgroungRemoverView::onOutputFolderCbbIndexChanged);
    connect(m_pOpenOutputFolderBtn, &QPushButton::clicked, this, &BackgroungRemoverView::onOpenOutputFolderBtnClicked);
    connect(m_pStartAllBtn, &QPushButton::clicked, this, &BackgroungRemoverView::onStartAllBtnClicked);
}

void BackgroungRemoverView::firstShow() {
    static bool firstShow = true;
    if(firstShow) {
        firstShow = false;
        initOutputFolderCbbItem();
    }
}

QWidget *BackgroungRemoverView::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("BackgroungRemoverView_DividingLine");
    dividingLine->setFixedHeight(1);
    return dividingLine;
}

void BackgroungRemoverView::listViewImportFile(const QStringList &filePaths) {
    BackgroungRemoverPresenter *prst = dynamic_cast<BackgroungRemoverPresenter *>(presenter());
    prst->appendData(filePaths);
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
    selectAllState();
}

void BackgroungRemoverView::onListModeSwitchBtnClicked() {
    BackgroungRemoverPresenter *prst = dynamic_cast<BackgroungRemoverPresenter *>(presenter());
    if (!prst->datas().isEmpty()) {
        m_pListDelegate->setListMode(!m_pListDelegate->isListMode());
        m_pListModeSwitchBtn->setText(m_pListDelegate->isListMode() ? QChar(0xe634) : QChar(0xe634));
        m_pListView->changeData(prst->datas());
        if(m_pListModeSwitchBtn->fourPixmapPath().contains("thumbnail")) {
            m_pListModeSwitchBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/icon/icon_state/icon24/icon24_list.png");
        }
        else {
            m_pListModeSwitchBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/icon/icon_state/icon24/icon24_thumbnail.png");
        }
    }
}

void BackgroungRemoverView::listItemSelectChanged(const QString &filePath) {
    BackgroungRemoverPresenter *prst = dynamic_cast<BackgroungRemoverPresenter *>(presenter());
    prst->switchCheckedData(filePath);
    m_pListView->changeData(prst->datas());
    blockSignalsFunc(m_pSelectAllCkb, [&]() {
        selectAllState();
    });
}

void BackgroungRemoverView::listItemDelete(const QString &filePath) {
    BackgroungRemoverPresenter *prst = dynamic_cast<BackgroungRemoverPresenter *>(presenter());
    QStringList filePaths;
    filePaths.append(filePath);
    prst->deleteData(filePaths);
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
    selectAllState();
}

void BackgroungRemoverView::listViewNoDataState() {
    BackgroungRemoverPresenter *prst = dynamic_cast<BackgroungRemoverPresenter *>(presenter());
    bool isNoData = prst->datas().isEmpty();
    m_pClearFileBtn->setVisible(!isNoData);
    m_pListModeSwitchBtn->setVisible(!isNoData);
    m_pSelectAllCkb->setVisible(!isNoData);
    m_pStackedLayout->setCurrentWidget(isNoData ? m_pImportGuideWidget : m_pWorkspaceWidget);
}

void BackgroungRemoverView::selectAllState() {
    BackgroungRemoverPresenter *prst = dynamic_cast<BackgroungRemoverPresenter *>(presenter());
    if (!prst->datas().isEmpty()) {
        for (auto data : prst->datas()) {
            if (!data.is_checked) {
                m_pSelectAllCkb->setChecked(false);
                return;
            }
        }
        m_pSelectAllCkb->setChecked(true);
    } else {
        m_pSelectAllCkb->setChecked(false);
    }
}

void BackgroungRemoverView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->backgroungRemoverOutPath());
    m_pOutputFolderCbb->addItem("...");
}

void BackgroungRemoverView::BackgroungRemoverView::setOutputFolder(const QString &path) {
    SETTINGS->setBackgroungRemoverOutPath(path);
    m_pOutputFolderCbb->setItemText(0, path);
}

void BackgroungRemoverView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Backgroung Remover"));
    m_pSelectAllCkb->setText(tr("Select All"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pStartAllBtn->setText(tr("Start"));
}

void BackgroungRemoverView::onAddFileBtnClicked() {
    QString title = tr("Open");
    QString directory = SETTINGS->backgroungRemoverLastAddFilePath();
    QStringList filePaths = QFileDialog::getOpenFileNames(this, title, directory, "All Files (*)");
    if (!filePaths.isEmpty()) {
        QFileInfo fileInfo(filePaths.first());
        QString lastDirectory = fileInfo.absolutePath();
        SETTINGS->setBackgroungRemoverLastAddFilePath(lastDirectory);
        listViewImportFile(filePaths);
    }
}

void BackgroungRemoverView::onAddFolderBtnClicked() {
    QString title = tr("Select Folder");
    QString folderPath = QFileDialog::getExistingDirectory(this, title, SETTINGS->backgroungRemoverLastAddFolderPath());
    if (!folderPath.isEmpty()) {
        SETTINGS->setBackgroungRemoverLastAddFolderPath(folderPath);
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

void BackgroungRemoverView::onClearFileBtnClicked() {
    BackgroungRemoverPresenter *prst = dynamic_cast<BackgroungRemoverPresenter *>(presenter());
    prst->clearData();
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
}

void BackgroungRemoverView::onSelectAllStateChanged(int state) {
    BackgroungRemoverPresenter *prst = dynamic_cast<BackgroungRemoverPresenter *>(presenter());
    prst->checkedAllData(state);
    m_pListView->changeData(prst->datas());
}

void BackgroungRemoverView::onListViewClicked(const QModelIndex &index) {
    auto data = index.data(Qt::UserRole).value<SBGRemoverData>();
    QRect rc = m_pListView->visualRect(index);
    int posx = m_pListView->mapFromGlobal(QCursor::pos()).x();
    int posy = m_pListView->mapFromGlobal(QCursor::pos()).y();
    auto bgRect = rc.adjusted(0, 0, -8, -8);
    auto checkedRect = QRect(bgRect.x() + 4, bgRect.y() + 4, 16, 16);
    auto delRect = QRect(bgRect.right() - 4 - 16, bgRect.y() + 4, 16, 16);
    if (posx >= delRect.x() && posx <= delRect.x() + delRect.width()
        && posy >= delRect.y() && posy <= delRect.y() + delRect.height()) {
        listItemDelete(data.file_path);
    }
    if (posx >= checkedRect.x() && posx <= checkedRect.x() + checkedRect.width()
        && posy >= checkedRect.y() && posy <= checkedRect.y() + checkedRect.height()) {
        listItemSelectChanged(data.file_path);
    }
}

void BackgroungRemoverView::onOutputFolderCbbClicked() {
}

void BackgroungRemoverView::onOutputFolderCbbIndexChanged(int index) {
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

void BackgroungRemoverView::onOpenOutputFolderBtnClicked() {
    QString folderPath = SETTINGS->backgroungRemoverOutPath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
}

void BackgroungRemoverView::onStartAllBtnClicked() {
    BackgroungRemoverPresenter *prst = dynamic_cast<BackgroungRemoverPresenter *>(presenter());
    // BackgroungRemoverTask task;
    // for(auto data : prst->datas()) {
    //     if(data.is_checked) {
    //         task.exec(data.file_path, SETTINGS->conversionOutPath(), SETTINGS->conversionOutFormat());
    //     }
    // }
}