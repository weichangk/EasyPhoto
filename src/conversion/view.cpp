#include "conversion/view.h"
#include "conversion/presenter.h"
#include "conversion/define.h"
#include "settings.h"
#include "conversion/conversiontask.h"
#include "import/importfilehelper.h"
#include "task/asynctask.h"
#include "task/taskfactory.h"
#include "task/taskdata.h"
#include "task/taskresult.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>

using namespace qtmaterialtask;

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
    m_pCancelAllBtn->setGeometry(width() - 110 - 16, (84 - 32) / 2, 110, 32);
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
    m_pSelectAllCkb->setObjectName("ConversionView_m_pSelectAllCkb");
    m_pSelectAllCkb->setVisible(false);

    m_pListModeSwitchBtn = new IconButton(topWidget);
    m_pListModeSwitchBtn->setFixedSize(24, 24);
    m_pListModeSwitchBtn->setIconSize(24, 24);
    m_pListModeSwitchBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/icon/icon_state/icon24/icon24_thumbnail.png");
    m_pListModeSwitchBtn->setVisible(false);

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

    initOutputFormatCbbItem();

    m_pOutputFolderLbl = new QLabel(bottomWidget);
    m_pOutputFolderLbl->setObjectName("ConversionView_m_pOutputFolderLbl");

    m_pOutputFolderCbb = new QComboBox(bottomWidget);
    m_pOutputFolderCbb->setFixedSize(226, 24);

    initOutputFolderCbbItem();

    m_pOpenOutputFolderBtn = new IconButton(bottomWidget);
    m_pOpenOutputFolderBtn->setFixedSize(24, 24);
    m_pOpenOutputFolderBtn->setIconSize(24, 24);
    m_pOpenOutputFolderBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/icon/icon_state/icon24/icon24_file.png");

    m_pStartAllBtn = new QPushButton(bottomWidget);
    m_pStartAllBtn->setObjectName("ConversionView_m_pStartAllBtn");
    m_pStartAllBtn->setFixedSize(110, 32);

    m_pCancelAllBtn = new QPushButton(bottomWidget);
    m_pCancelAllBtn->setObjectName("ConversionView_m_pStartAllBtn");
    m_pCancelAllBtn->setFixedSize(110, 32);

    setStartAllBtnVisible(true);

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

    m_pListViewColumnName = new QWidget(this);
    m_pListViewColumnName->setObjectName("ConversionView_m_pListViewColumnName");
    m_pListViewColumnName->setFixedHeight(40);
    auto listViewColumnNameLayout = new QHBoxLayout(m_pListViewColumnName);
    listViewColumnNameLayout->setContentsMargins(24, 0, 60, 0);
    listViewColumnNameLayout->setSpacing(0);
    m_pColumnFileNameCkb = new QCheckBox(m_pListViewColumnName);
    m_pColumnFileNameCkb->setObjectName("ConversionView_m_pColumnFileNameCkb");
    m_pColumnResolutionLbl = new QLabel(m_pListViewColumnName);
    m_pColumnResolutionLbl->setObjectName("ConversionView_m_pColumnLbl");
    m_pColumnOutputFormatLbl = new QLabel(m_pListViewColumnName);
    m_pColumnOutputFormatLbl->setObjectName("ConversionView_m_pColumnLbl");
    m_pColumnStatusLbl = new QLabel(m_pListViewColumnName);
    m_pColumnStatusLbl->setObjectName("ConversionView_m_pColumnLbl");
    m_pColumnActionLbl = new QLabel(m_pListViewColumnName);
    m_pColumnActionLbl->setObjectName("ConversionView_m_pColumnLbl");

    listViewColumnNameLayout->addWidget(m_pColumnFileNameCkb, 1);
    listViewColumnNameLayout->addStretch();
    listViewColumnNameLayout->addWidget(m_pColumnResolutionLbl);
    listViewColumnNameLayout->addSpacing(60);
    listViewColumnNameLayout->addWidget(m_pColumnOutputFormatLbl);
    listViewColumnNameLayout->addSpacing(60);
    listViewColumnNameLayout->addWidget(m_pColumnStatusLbl);
    listViewColumnNameLayout->addSpacing(60);
    listViewColumnNameLayout->addWidget(m_pColumnActionLbl);

    m_pListView = new ListView<SConversionData>(this);
    m_pListView->setSpacing(0);
    m_pListDelegate = new ConversionListDelegate(m_pListView);
    m_pListView->setItemDelegate(m_pListDelegate);
    m_pListView->setItemDelegateForColumn(0, m_pListDelegate);
    m_pListView->setMouseTracking(true);
    m_pListView->setEditTriggers(QListView::AllEditTriggers);
    m_pListView->viewport()->installEventFilter(m_pListDelegate);
    auto listViewLayout = new QVBoxLayout();
    listViewLayout->setContentsMargins(0, 0, 0, 0);
    listViewLayout->setSpacing(0);
    listViewLayout->addWidget(m_pListViewColumnName);
    listViewLayout->addWidget(m_pListView, 1);

    m_pContentWidget = new QWidget(this);
    auto contentWidgetLayout = new QVBoxLayout(m_pContentWidget);
    contentWidgetLayout->setContentsMargins(0, 0, 0, 0);
    contentWidgetLayout->setSpacing(0);
    contentWidgetLayout->addWidget(topWidget);
    contentWidgetLayout->addWidget(createDividingLine());
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
    // connect(m_pSelectAllCkb, &QCheckBox::stateChanged, this, &ConversionView::onSelectAllStateChanged);
    connect(m_pColumnFileNameCkb, &QCheckBox::stateChanged, this, &ConversionView::onSelectAllStateChanged);
    connect(m_pListModeSwitchBtn, &QPushButton::clicked, this, &ConversionView::onListModeSwitchBtnClicked);
    connect(m_pListView, &QListView::clicked, this, &ConversionView::onListViewClicked);
    connect(m_pOutputFormatCbb, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentTextChanged), this, &ConversionView::onOutputFormatCbbCurrentTextChanged);
    connect(m_pOutputFolderCbb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ConversionView::onOutputFolderCbbIndexChanged);
    connect(m_pOpenOutputFolderBtn, &QPushButton::clicked, this, &ConversionView::onOpenOutputFolderBtnClicked);
    connect(m_pStartAllBtn, &QPushButton::clicked, this, &ConversionView::onStartAllBtnClicked);
    connect(m_pCancelAllBtn, &QPushButton::clicked, this, &ConversionView::onCancelAllBtnClicked);
    connect(m_pListDelegate, &ConversionListDelegate::sigUpdateData, this, [this](const SConversionData &data) {
        ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
        prst->updateData(data);
    });
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
    // prst->appendData(filePaths);
    // m_pListView->changeData(prst->datas());
    // listViewNoDataState();
    // selectAllState();
    ImportFileHelper ihp;
    connect(&ihp, &ImportFileHelper::sigSucceeded, this, [this, prst](const QVariant &result) {
        SImportFileResult<QList<SConversionData>> res = result.value<SImportFileResult<QList<SConversionData>>>();
        prst->appendData(res.value);
        m_pListView->changeData(prst->datas());
        listViewNoDataState();
        selectAllState();
    });
    ihp.start<SImportFileData, SImportFileResult<QList<SConversionData>>>(
        [prst](AsyncTask<SImportFileData, SImportFileResult<QList<SConversionData>>> *task) {
            return prst->importFileAsync(task);
        },
        TaskData<SImportFileData>({filePaths})
    );
}

void ConversionView::onListModeSwitchBtnClicked() {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    if (!prst->datas().isEmpty()) {
        m_pListDelegate->setListMode(!m_pListDelegate->isListMode());
        m_pListModeSwitchBtn->setText(m_pListDelegate->isListMode() ? QChar(0xe634) : QChar(0xe634));
        m_pListView->changeData(prst->datas());
        if (m_pListModeSwitchBtn->fourPixmapPath().contains("thumbnail")) {
            m_pListModeSwitchBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/icon/icon_state/icon24/icon24_list.png");
        } else {
            m_pListModeSwitchBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/icon/icon_state/icon24/icon24_thumbnail.png");
        }
    }
}

void ConversionView::listItemSelectChanged(const QString &filePath) {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    prst->switchCheckedData(filePath);
    m_pListView->changeData(prst->datas());
    // blockSignalsFunc(m_pSelectAllCkb, [&]() {
    //     selectAllState();
    // });
    blockSignalsFunc(m_pColumnFileNameCkb, [&]() {
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
    // m_pListModeSwitchBtn->setVisible(!isNoData);
    // m_pSelectAllCkb->setVisible(!isNoData);
    m_pColumnFileNameCkb->setVisible(!isNoData);
    m_pStackedLayout->setCurrentWidget(isNoData ? m_pImportGuideWidget : m_pContentWidget);
}

void ConversionView::selectAllState() {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    if (!prst->datas().isEmpty()) {
        for (auto data : prst->datas()) {
            if (!data.is_checked) {
                // m_pSelectAllCkb->setChecked(false);
                m_pColumnFileNameCkb->setChecked(false);
                return;
            }
        }
        // m_pSelectAllCkb->setChecked(true);
        m_pColumnFileNameCkb->setChecked(true);
    } else {
        // m_pSelectAllCkb->setChecked(false);
        m_pColumnFileNameCkb->setChecked(false);
    }
}

void ConversionView::initOutputFormatCbbItem() {
    QString format = CONV_OUTPUT_FORMATS;
    QStringList formats = format.split(' ');
    QList<SConversionOuputFormat> formatDatas;
    for (auto &item : formats) {
        m_pOutputFormatCbb->addItem(item.toUpper());
    }
    blockSignalsFunc(m_pOutputFormatCbb, [&]() {
        m_pOutputFormatCbb->setCurrentText(SETTINGS->conversionOutFormat().toUpper());
    });
}

void ConversionView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->conversionOutPath());
    m_pOutputFolderCbb->addItem("...");
}

void ConversionView::ConversionView::setOutputFolder(const QString &path) {
    SETTINGS->setConversionOutPath(path);
    m_pOutputFolderCbb->setItemText(0, path);
}

void ConversionView::setStartAllBtnVisible(bool visible) {
    m_pStartAllBtn->setVisible(visible);
    m_pCancelAllBtn->setVisible(!visible);
}

QList<SConversionData> ConversionView::getListViewModels() const {
    QList<SConversionData> datas;
    for (int i = 0; i < m_pListView->model()->rowCount(); ++i) {
        auto index = m_pListView->model()->index(i, 0);
        auto data = index.data(Qt::UserRole).value<SConversionData>();
        datas.append(data);
    }
    return datas;
}

SConversionData ConversionView::getListViewModel(const QString &filePath) const {
    for (int i = 0; i < m_pListView->model()->rowCount(); ++i) {
        auto index = m_pListView->model()->index(i, 0);
        auto data = index.data(Qt::UserRole).value<SConversionData>();
        if (data.file_path == filePath) {
            return data;
        }
    }
    return SConversionData();
}

int ConversionView::getListViewModelIndex(const QString &filePath) const {
    for (int i = 0; i < m_pListView->model()->rowCount(); ++i) {
        auto index = m_pListView->model()->index(i, 0);
        auto data = index.data(Qt::UserRole).value<SConversionData>();
        if (data.file_path == filePath) {
            return i;
        }
    }
    return -1;
}

void ConversionView::startConvAllTask() {
    auto func = [this](AsyncTask<void*, void*> *task) -> TaskResult<void*> {
        ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
        ConversionTask convTask;
        for (auto data : prst->datas()) {
            if(m_pStartAllBtn->isVisible()) {
                return TaskResult<void*>::Success(nullptr);
            }
            if (data.is_checked) {
                data.state = EConvState_Loading; 
                prst->updateData(data.file_path, data);
                m_pListView->changeData(getListViewModelIndex(data.file_path), data);
                auto result = convTask.exec(SConvParam{
                    data.file_path.toStdString(),
                    SETTINGS->conversionOutPath().toStdString(),
                    data.output_format.toStdString()});
                data.state = result.success ?  EConvState_Success : EConvState_Fail; 
                prst->updateData(data.file_path, data);
                m_pListView->changeData(getListViewModelIndex(data.file_path), data);
            }
        }

        QMetaObject::invokeMethod(this, [this]() {
            setStartAllBtnVisible(true);
        }, Qt::QueuedConnection);

        return TaskResult<void*>::Success(nullptr);
    };
    auto task = TaskFactory::instance()->createTask<void*, void*>(func, nullptr, TaskData<void*>());
    task->start();
}

void ConversionView::startConvTask(const QString &path) {
    auto func = [this, path](AsyncTask<void*, void*> *task) -> TaskResult<void*> {
        ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
        ConversionTask convTask;
        for (auto data : prst->datas()) {
            if (data.file_path == path && data.state != EConvState_Loading) {
                data.state = EConvState_Loading; 
                prst->updateData(data.file_path, data);
                m_pListView->changeData(getListViewModelIndex(data.file_path), data);
                auto result = convTask.exec(SConvParam{
                    data.file_path.toStdString(),
                    SETTINGS->conversionOutPath().toStdString(),
                    data.output_format.toStdString()});
                data.state = result.success ?  EConvState_Success : EConvState_Fail; 
                prst->updateData(data.file_path, data);
                m_pListView->changeData(getListViewModelIndex(data.file_path), data);
                return TaskResult<void*>::Success(nullptr);
            }
        }
        return TaskResult<void*>::Success(nullptr);
    };
    auto task = TaskFactory::instance()->createTask<void*, void*>(func, nullptr, TaskData<void*>());
    task->start();
}

void ConversionView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Converter"));
    m_pSelectAllCkb->setText(tr("Select All"));
    m_pOutputFormatLbl->setText(tr("Output format:"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pStartAllBtn->setText(tr("Convert All"));
    m_pCancelAllBtn->setText(tr("Cancel All"));

    m_pColumnFileNameCkb->setText(tr("File Name"));
    m_pColumnResolutionLbl->setText(tr("Resolution"));
    m_pColumnOutputFormatLbl->setText(tr("Output Format"));
    m_pColumnStatusLbl->setText(tr("Status"));
    m_pColumnActionLbl->setText(tr("Action"));
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
    auto bgRect = rc.adjusted(0, 0, 0, 0);
    auto checkedRect = convListCheckedRect(bgRect);
    auto delRect = convListDelRect(bgRect);
    auto convRect = convListConvRect(bgRect);
    if (posx >= delRect.x() && posx <= delRect.x() + delRect.width()
        && posy >= delRect.y() && posy <= delRect.y() + delRect.height()) {
        listItemDelete(data.file_path);
    }
    if (posx >= checkedRect.x() && posx <= checkedRect.x() + checkedRect.width()
        && posy >= checkedRect.y() && posy <= checkedRect.y() + checkedRect.height()) {
        listItemSelectChanged(data.file_path);
    }
    if (posx >= convRect.x() && posx <= convRect.x() + convRect.width()
        && posy >= convRect.y() && posy <= convRect.y() + convRect.height()) {
        startConvTask(data.file_path);
    }
}

void ConversionView::onOutputFormatCbbCurrentTextChanged(const QString &text) {
    QString format = text.toLower();
    SETTINGS->setConversionOutFormat(format);
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    for (auto &data : prst->datas()) {
        data.output_format = format; 
        prst->updateData(data.file_path, data);
    }
    m_pListView->changeData(prst->datas());
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
    setStartAllBtnVisible(false);
    startConvAllTask();
}

void ConversionView::onCancelAllBtnClicked() {
    setStartAllBtnVisible(true);
}