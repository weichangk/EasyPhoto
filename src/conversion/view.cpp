#include "conversion/view.h"
#include "conversion/presenter.h"
#include "settings.h"
#include "conversion/conversiontask.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>

ConversionOutputFormatView::ConversionOutputFormatView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void ConversionOutputFormatView::setSelection(const QString &format) {
    for (int row = 0; row < m_pListView->count(); ++row) {
        auto data = m_pListView->data(row);
        if (data.name == format) {
            QModelIndex index = m_pListView->index(row);
            m_pListView->setCurrentIndex(index);
        }
    }
}

void ConversionOutputFormatView::createUi() {
    setObjectName("OutputFormatView");
    setAttribute(Qt::WA_StyledBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(281, 152);

    auto popup = new PopupWindow(this);
    auto mask = new MaskWidget(this);
    mask->setPramas(MaskWidget::RoundType::Round_All, 0, 8, 8);

    m_pListView = new ListView<SConversionOuputFormat>(this);
    m_pListView->setSpacing(0);
    m_pListDelegate = new ConversionOutputFormatDelegate(m_pListView);
    m_pListView->setItemDelegate(m_pListDelegate);
    m_pListView->viewport()->installEventFilter(m_pListDelegate);
    m_pListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QString format = CONV_OUTPUT_FORMATS;
    QStringList formats = format.split(' ');
    QList<SConversionOuputFormat> formatDatas;
    for (auto &item : formats) {
        SConversionOuputFormat format = {item, item.toUpper(), nullptr, false};
        formatDatas.append(format);
    }
    m_pListView->changeData(formatDatas);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_pListView, 1);
}

void ConversionOutputFormatView::connectSig() {
    connect(m_pListView, &QListView::clicked, this, &ConversionOutputFormatView::onListItemViewclicked);
}

void ConversionOutputFormatView::onListItemViewclicked(const QModelIndex &index) {
    auto data = m_pListView->data(index);
    SETTINGS->setConversionOutFormat(data.name);
    emit sigSelectionChanged(data.name);
    close();
}

ConversionView::ConversionView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

void ConversionView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    listViewNoDataState();
    selectAllState();
}

void ConversionView::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    m_pOutputFormatLbl->setGeometry(16, 14, 100, 24);
    m_pOutputFormatCbb->setGeometry(m_pOutputFormatLbl->geometry().right() + 6, 14, 226, 24);

    m_pOutputFolderLbl->setGeometry(16, 44, 100, 24);
    m_pOutputFolderCbb->setGeometry(m_pOutputFolderLbl->geometry().right() + 6, 44, 226, 24);
    m_pOpenOutputFolderBtn->setGeometry(m_pOutputFolderCbb->geometry().right() + 6, 44, 24, 24);

    m_pStartAllBtn->setGeometry(width() - 110 - 16, (84 - 32) / 2, 110, 32);
}

void ConversionView::createUi() {
    setObjectName("ConversionView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setObjectName("ConversionView_m_pTitleLbl");
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

    m_pSelectAllCkb = new QCheckBox(topWidget);
    m_pSelectAllCkb->setObjectName("ConversionView_m_pSelectAllCkb");

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
    topWidgetLayout->addWidget(m_pSelectAllCkb);
    topWidgetLayout->addWidget(m_pClearFileBtn);
    topWidgetLayout->addWidget(m_pListModeSwitchBtn);

    QWidget *bottomWidget = new QWidget(this);
    bottomWidget->setFixedHeight(84);

    m_pOutputFormatLbl = new QLabel(bottomWidget);
    m_pOutputFormatLbl->setObjectName("ConversionView_m_pOutputFormatLbl");

    m_pOutputFormatCbb = new QComboBox(bottomWidget);
    m_pOutputFormatCbb->setFixedSize(226, 24);

    m_pOutputFormatEdit = new QLineEdit(m_pOutputFormatCbb);
    m_pOutputFormatEdit->setReadOnly(true);
    m_pOutputFormatCbb->setLineEdit(m_pOutputFormatEdit);

    setOutputFormatCbbText(SETTINGS->conversionOutFormat());

    m_pOutputFormatCbbFilter = new ComboBoxFilter(m_pOutputFormatCbb);
    m_pOutputFormatCbb->installEventFilter(m_pOutputFormatCbbFilter);

    m_pOutputFolderLbl = new QLabel(bottomWidget);
    m_pOutputFolderLbl->setObjectName("ConversionView_m_pOutputFolderLbl");

    m_pOutputFolderCbb = new QComboBox(bottomWidget);
    m_pOutputFolderCbb->setFixedSize(226, 24);

    m_pOutputFolderCbbFilter = new ComboBoxFilter(m_pOutputFolderCbb);
    m_pOutputFolderCbb->installEventFilter(m_pOutputFolderCbbFilter);

    initOutputFolderCbbItem();

    m_pOpenOutputFolderBtn = new IconButton(bottomWidget);
    m_pOpenOutputFolderBtn->setFixedSize(24, 24);
    m_pOpenOutputFolderBtn->setIconSize(24, 24);
    m_pOpenOutputFolderBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/old/icon/icon_state/icon24/icon24_file.png");

    m_pStartAllBtn = new QPushButton(bottomWidget);
    m_pStartAllBtn->setObjectName("ConversionView_m_pStartAllBtn");
    m_pStartAllBtn->setFixedSize(110, 32);

    // auto bottomWidgetLayout = new QHBoxLayout(bottomWidget);
    // bottomWidgetLayout->setContentsMargins(20, 0, 20, 0);
    // bottomWidgetLayout->setSpacing(0);
    // bottomWidgetLayout->addWidget(m_pOutputFormatLbl);
    // bottomWidgetLayout->addSpacing(4);
    // bottomWidgetLayout->addWidget(m_pOutputFormatCbb);
    // bottomWidgetLayout->addSpacing(12);
    // bottomWidgetLayout->addWidget(m_pOutputFolderLbl);
    // bottomWidgetLayout->addSpacing(4);
    // bottomWidgetLayout->addWidget(m_pOutputFolderCbb);
    // bottomWidgetLayout->addSpacing(4);
    // bottomWidgetLayout->addWidget(m_pOpenOutputFolderBtn);
    // bottomWidgetLayout->addStretch();
    // bottomWidgetLayout->addWidget(m_pStartAllBtn);

    m_pListView = new ListView<SConversionData>(this);
    m_pListView->setSpacing(0);
    m_pListDelegate = new ConversionListDelegate(m_pListView);
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

void ConversionView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &ConversionView::onLanguageChange);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &ConversionView::listViewImportFile);
    connect(m_pAddFileBtn, &QPushButton::clicked, this, &ConversionView::onAddFileBtnClicked);
    connect(m_pAddFolderBtn, &QPushButton::clicked, this, &ConversionView::onAddFolderBtnClicked);
    connect(m_pClearFileBtn, &QPushButton::clicked, this, &ConversionView::onClearFileBtnClicked);
    connect(m_pSelectAllCkb, &QCheckBox::stateChanged, this, &ConversionView::onSelectAllStateChanged);
    connect(m_pListModeSwitchBtn, &QPushButton::clicked, this, &ConversionView::onListModeSwitchBtnClicked);
    connect(m_pListView, &QListView::clicked, this, &ConversionView::onListViewClicked);
    connect(m_pOutputFormatCbbFilter, &ComboBoxFilter::sigClicked, this, &ConversionView::onOutputFormatCbbClicked);
    connect(m_pOutputFolderCbbFilter, &ComboBoxFilter::sigClicked, this, &ConversionView::onOutputFolderCbbClicked);
    connect(m_pOutputFolderCbb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ConversionView::onOutputFolderCbbIndexChanged);
    connect(m_pOpenOutputFolderBtn, &QPushButton::clicked, this, &ConversionView::onOpenOutputFolderBtnClicked);
    connect(m_pStartAllBtn, &QPushButton::clicked, this, &ConversionView::onStartAllBtnClicked);
}

QWidget *ConversionView::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("ConversionView_DividingLine");
    dividingLine->setFixedHeight(1);
    return dividingLine;
}

void ConversionView::listViewImportFile(const QStringList &filePaths) {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    prst->appendData(filePaths);
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
    selectAllState();
}

void ConversionView::onListModeSwitchBtnClicked() {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    if (!prst->datas().isEmpty()) {
        m_pListDelegate->setListMode(!m_pListDelegate->isListMode());
        m_pListModeSwitchBtn->setText(m_pListDelegate->isListMode() ? QChar(0xe634) : QChar(0xe634));
        m_pListView->changeData(prst->datas());
        if (m_pListModeSwitchBtn->fourPixmapPath().contains("thumbnail")) {
            m_pListModeSwitchBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/old/icon/icon_state/icon24/icon24_list.png");
        } else {
            m_pListModeSwitchBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/old/icon/icon_state/icon24/icon24_thumbnail.png");
        }
    }
}

void ConversionView::listItemSelectChanged(const QString &filePath) {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    prst->switchCheckedData(filePath);
    m_pListView->changeData(prst->datas());
    blockSignalsFunc(m_pSelectAllCkb, [&]() {
        selectAllState();
    });
}

void ConversionView::listItemDelete(const QString &filePath) {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    QStringList filePaths;
    filePaths.append(filePath);
    prst->deleteData(filePaths);
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
    selectAllState();
}

void ConversionView::listViewNoDataState() {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    bool isNoData = prst->datas().isEmpty();
    m_pClearFileBtn->setVisible(!isNoData);
    m_pListModeSwitchBtn->setVisible(!isNoData);
    m_pSelectAllCkb->setVisible(!isNoData);
    m_pStackedLayout->setCurrentWidget(isNoData ? m_pImportGuideWidget : m_pContentWidget);
}

void ConversionView::selectAllState() {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
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

void ConversionView::showOutputFormatView() {
    if (!m_pOutputFormatView) {
        m_pOutputFormatView = new ConversionOutputFormatView(this);
        connect(m_pOutputFormatView, &ConversionOutputFormatView::sigSelectionChanged, this, &ConversionView::setOutputFormatCbbText);
    }

    m_pOutputFormatView->setSelection(SETTINGS->conversionOutFormat());

    auto btnPos = m_pOutputFormatCbb->mapToGlobal(QPoint(0, 0));
    auto pos = btnPos - QPoint(0, m_pOutputFormatView->height() + 8);

    m_pOutputFormatView->move(pos);
    m_pOutputFormatView->show();
}

void ConversionView::setOutputFormatCbbText(const QString &text) {
    m_pOutputFormatEdit->setText(text.toUpper());
}

void ConversionView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->conversionOutPath());
    m_pOutputFolderCbb->addItem("...");
}

void ConversionView::ConversionView::setOutputFolder(const QString &path) {
    SETTINGS->setConversionOutPath(path);
    m_pOutputFolderCbb->setItemText(0, path);
}

void ConversionView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Converter"));
    m_pSelectAllCkb->setText(tr("Select All"));
    m_pOutputFormatLbl->setText(tr("Output format:"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pStartAllBtn->setText(tr("Convert All"));
}

void ConversionView::onAddFileBtnClicked() {
    QString title = tr("Open");
    QString directory = SETTINGS->conversionLastAddFilePath();
    QStringList filePaths = QFileDialog::getOpenFileNames(this, title, directory, "All Files (*)");
    if (!filePaths.isEmpty()) {
        QFileInfo fileInfo(filePaths.first());
        QString lastDirectory = fileInfo.absolutePath();
        SETTINGS->setConversionLastAddFilePath(lastDirectory);
        listViewImportFile(filePaths);
    }
}

void ConversionView::onAddFolderBtnClicked() {
    QString title = tr("Select Folder");
    QString folderPath = QFileDialog::getExistingDirectory(this, title, SETTINGS->conversionLastAddFolderPath());
    if (!folderPath.isEmpty()) {
        SETTINGS->setConversionLastAddFolderPath(folderPath);
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

void ConversionView::onClearFileBtnClicked() {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    prst->clearData();
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
}

void ConversionView::onSelectAllStateChanged(int state) {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    prst->checkedAllData(state);
    m_pListView->changeData(prst->datas());
}

void ConversionView::onListViewClicked(const QModelIndex &index) {
    auto data = index.data(Qt::UserRole).value<SConversionData>();
    QRect rc = m_pListView->visualRect(index);
    int posx = m_pListView->mapFromGlobal(QCursor::pos()).x();
    int posy = m_pListView->mapFromGlobal(QCursor::pos()).y();
    auto bgRect = rc.adjusted(0, 0, -8, -8);
    auto checkedRect = QRect(bgRect.x() + 8, bgRect.y() + 8, 16, 16);
    auto delRect = QRect(bgRect.right() - 8 - 16, bgRect.y() + 8, 16, 16);
    if (posx >= delRect.x() && posx <= delRect.x() + delRect.width()
        && posy >= delRect.y() && posy <= delRect.y() + delRect.height()) {
        listItemDelete(data.file_path);
    }
    if (posx >= checkedRect.x() && posx <= checkedRect.x() + checkedRect.width()
        && posy >= checkedRect.y() && posy <= checkedRect.y() + checkedRect.height()) {
        listItemSelectChanged(data.file_path);
    }
}

void ConversionView::onOutputFormatCbbClicked() {
    showOutputFormatView();
}

void ConversionView::onOutputFolderCbbClicked() {
}

void ConversionView::onOutputFolderCbbIndexChanged(int index) {
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

void ConversionView::onOpenOutputFolderBtnClicked() {
    QString folderPath = SETTINGS->conversionOutPath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
}

void ConversionView::onStartAllBtnClicked() {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    ConversionTask task;
    for (auto data : prst->datas()) {
        if (data.is_checked) {
            task.exec(data.file_path, SETTINGS->conversionOutPath(), SETTINGS->conversionOutFormat());
        }
    }
}