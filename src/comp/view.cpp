#include "comp/view.h"
#include "comp/definerect.h"
#include "comp/presenter.h"
#include "comp/task.h"
#include "import/importfilehelper.h"
#include "task/asynctask.h"
#include "task/taskfactory.h"
#include "task/taskdata.h"
#include "task/taskresult.h"
#include "widget/messagebox.h"
#include "core/theme.h"
#include "settings.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>

CompView::CompView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

void CompView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    listViewNoDataState();
    selectAllState();
}

void CompView::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    m_pOutputFormatLbl->setGeometry(16, 14, 100, 24);
    m_pOutputFormatCbb->setGeometry(m_pOutputFormatLbl->geometry().right() + 6, 14, 226, 24);
    m_pCompreToLbl->setGeometry(m_pOutputFormatCbb->geometry().right() + 60, 14, 100, 24);
    m_pCompreSlider->setGeometry(m_pCompreToLbl->geometry().right() + 6, 14, 100, 24);
    m_pCompreValueEdit->setGeometry(m_pCompreSlider->geometry().right() + 6, 14, 48, 24);
    m_pComprePercentLbl->setGeometry(m_pCompreValueEdit->geometry().right() + 6, 14, 24, 24);

    m_pOutputFolderLbl->setGeometry(16, 44, 100, 24);
    m_pOutputFolderCbb->setGeometry(m_pOutputFolderLbl->geometry().right() + 6, 44, 226, 24);
    m_pOpenOutputFolderBtn->setGeometry(m_pOutputFolderCbb->geometry().right() + 6, 44, 24, 24);

    m_pStartAllBtn->setGeometry(width() - 110 - 16, (84 - 32) / 2, 110, 32);
    m_pCancelAllBtn->setGeometry(width() - 110 - 16, (84 - 32) / 2, 110, 32);
}

void CompView::createUi() {
    setObjectName("EP_BGView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setObjectName("QLbl_LH24_FS24_FW7");
    auto titleLabLayout = new QHBoxLayout();
    titleLabLayout->setContentsMargins(20, 0, 0, 0);
    titleLabLayout->addWidget(m_pTitleLbl, 0, Qt::AlignLeft);

    //
    m_pImportGuide = new ImportGuide(this, QString("Files %1").arg(COMP_INPUT_FORMATS));
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
    m_pAddFileBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/icon/icon_state/icon32/icon32_add_file.png").arg(QtmCore::Theme::currentTheme()));

    m_pAddFolderBtn = new IconButton(topWidget);
    m_pAddFolderBtn->setFixedSize(32, 32);
    m_pAddFolderBtn->setIconSize(32, 32);
    m_pAddFolderBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/icon/icon_state/icon32/icon32_add_folder.png").arg(QtmCore::Theme::currentTheme()));

    m_pClearFileBtn = new IconButton(topWidget);
    m_pClearFileBtn->setFixedSize(24, 24);
    m_pClearFileBtn->setIconSize(24, 24);
    m_pClearFileBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/icon/icon_state/icon24/icon24_delete.png").arg(QtmCore::Theme::currentTheme()));

    auto topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setContentsMargins(20, 0, 20, 0);
    topWidgetLayout->setSpacing(12);
    topWidgetLayout->addWidget(m_pAddFileBtn);
    topWidgetLayout->addWidget(m_pAddFolderBtn);
    topWidgetLayout->addStretch();
    topWidgetLayout->addWidget(m_pClearFileBtn);

    QWidget *bottomWidget = new QWidget(this);
    bottomWidget->setFixedHeight(84);

    m_pOutputFormatLbl = new QLabel(bottomWidget);
    m_pOutputFormatLbl->setObjectName("QLbl_LH16_FS12_FW4");

    m_pOutputFormatCbb = new QComboBox(bottomWidget);
    m_pOutputFormatCbb->setFixedSize(226, 24);

    initOutputFormatCbbItem();

    m_pOutputFolderLbl = new QLabel(bottomWidget);
    m_pOutputFolderLbl->setObjectName("QLbl_LH16_FS12_FW4");

    m_pOutputFolderCbb = new QComboBox(bottomWidget);
    m_pOutputFolderCbb->setFixedSize(226, 24);

    initOutputFolderCbbItem();

    m_pOpenOutputFolderBtn = new IconButton(bottomWidget);
    m_pOpenOutputFolderBtn->setFixedSize(24, 24);
    m_pOpenOutputFolderBtn->setIconSize(24, 24);
    m_pOpenOutputFolderBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/icon/icon_state/icon24/icon24_file.png").arg(QtmCore::Theme::currentTheme()));

    m_pCompreToLbl = new QLabel(bottomWidget);
    m_pCompreToLbl->setObjectName("QLbl_LH16_FS12_FW4");

    m_pCompreSlider = new QSlider(Qt::Horizontal, bottomWidget);
    m_pCompreSlider->setObjectName("CompView_m_pCompreSlider");
    m_pCompreSlider->setRange(1, 100);
    m_pCompreSlider->setTickInterval(1);
    m_pCompreSlider->setValue(SETTINGS->getCompSetting()->getQuality());

    m_pCompreValueEdit = new QLineEdit(bottomWidget);
    m_pCompreValueEdit->setObjectName("CompView_m_pCompreValueEdit");
    QIntValidator *validator = new QIntValidator(1, 100, m_pCompreValueEdit);
    m_pCompreValueEdit->setValidator(validator);
    m_pCompreValueEdit->setText(QString::number(SETTINGS->getCompSetting()->getQuality()));

    m_pComprePercentLbl = new QLabel(bottomWidget);
    m_pComprePercentLbl->setObjectName("QLbl_LH16_FS12_FW4");

    m_pStartAllBtn = new QPushButton(bottomWidget);
    m_pStartAllBtn->setObjectName("QPBtn_BR16_FS14_FW7");
    m_pStartAllBtn->setFixedSize(110, 32);

    m_pCancelAllBtn = new QPushButton(bottomWidget);
    m_pCancelAllBtn->setObjectName("QPBtn_BR16_FS14_FW7");
    m_pCancelAllBtn->setFixedSize(110, 32);

    setStartAllBtnVisible(true);

    m_pListViewColumnName = new QWidget(this);
    m_pListViewColumnName->setFixedHeight(40);
    auto listViewColumnNameLayout = new QHBoxLayout(m_pListViewColumnName);
    listViewColumnNameLayout->setContentsMargins(24, 0, 66, 0);
    listViewColumnNameLayout->setSpacing(0);
    m_pColumnFileNameCkb = new QCheckBox(m_pListViewColumnName);
    m_pColumnResolutionLbl = new QLabel(m_pListViewColumnName);
    m_pColumnResolutionLbl->setObjectName("QLbl_LH16_FS12_FW4");
    m_pColumnSizeLbl = new QLabel(m_pListViewColumnName);
    m_pColumnSizeLbl->setObjectName("QLbl_LH16_FS12_FW4");
    m_pColumnStatusLbl = new QLabel(m_pListViewColumnName);
    m_pColumnStatusLbl->setObjectName("QLbl_LH16_FS12_FW4");
    m_pColumnActionLbl = new QLabel(m_pListViewColumnName);
    m_pColumnActionLbl->setObjectName("QLbl_LH16_FS12_FW4");

    listViewColumnNameLayout->addWidget(m_pColumnFileNameCkb, 1);
    listViewColumnNameLayout->addStretch();
    listViewColumnNameLayout->addWidget(m_pColumnResolutionLbl);
    listViewColumnNameLayout->addSpacing(84 + 16);
    listViewColumnNameLayout->addWidget(m_pColumnSizeLbl);
    listViewColumnNameLayout->addSpacing(78 + 45);
    listViewColumnNameLayout->addWidget(m_pColumnStatusLbl);
    listViewColumnNameLayout->addSpacing(70);
    listViewColumnNameLayout->addWidget(m_pColumnActionLbl);

    m_pListView = new ListView<SImageData>(this);
    m_pListView->setSpacing(0);
    m_pListDelegate = new CompListDelegate(m_pListView);
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

void CompView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &CompView::onLanguageChange);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &CompView::listViewImportFile);
    connect(m_pAddFileBtn, &QPushButton::clicked, this, &CompView::onAddFileBtnClicked);
    connect(m_pAddFolderBtn, &QPushButton::clicked, this, &CompView::onAddFolderBtnClicked);
    connect(m_pClearFileBtn, &QPushButton::clicked, this, &CompView::onClearFileBtnClicked);
    connect(m_pColumnFileNameCkb, &QCheckBox::stateChanged, this, &CompView::onSelectAllStateChanged);
    connect(m_pListView, &QListView::clicked, this, &CompView::onListViewClicked);
    connect(m_pOutputFormatCbb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CompView::onOutputFormatCbbCurrentIndex);
    connect(m_pOutputFolderCbb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &CompView::onOutputFolderCbbIndexChanged);
    connect(m_pOpenOutputFolderBtn, &QPushButton::clicked, this, &CompView::onOpenOutputFolderBtnClicked);
    connect(m_pStartAllBtn, &QPushButton::clicked, this, &CompView::onStartAllBtnClicked);
    connect(m_pCancelAllBtn, &QPushButton::clicked, this, &CompView::onCancelAllBtnClicked);
    connect(m_pCompreSlider, &QSlider::valueChanged, this, &CompView::onCompreSliderValueChanged);
    connect(m_pCompreValueEdit, &QLineEdit::textEdited, this, &CompView::onCompreValueEdited);
}

QWidget *CompView::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("EP_Line");
    dividingLine->setFixedHeight(1);
    return dividingLine;
}

void CompView::listViewImportFile(const QStringList &filePaths) {
    CompPresenter *prst = dynamic_cast<CompPresenter *>(presenter());
    prst->appendData(filePaths);
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
    selectAllState();
}

void CompView::listItemSelectChanged(const QString &filePath) {
    CompPresenter *prst = dynamic_cast<CompPresenter *>(presenter());
    prst->switchCheckedData(filePath);
    m_pListView->changeData(prst->datas());
    blockSignalsFunc(m_pColumnFileNameCkb, [&]() {
        selectAllState();
    });
}

void CompView::listItemDelete(const QString &filePath) {
    CompPresenter *prst = dynamic_cast<CompPresenter *>(presenter());
    QStringList filePaths;
    filePaths.append(filePath);
    prst->deleteData(filePaths);
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
    selectAllState();
}

void CompView::listViewNoDataState() {
    CompPresenter *prst = dynamic_cast<CompPresenter *>(presenter());
    bool isNoData = prst->datas().isEmpty();
    m_pClearFileBtn->setVisible(!isNoData);
    m_pColumnFileNameCkb->setVisible(!isNoData);
    m_pStackedLayout->setCurrentWidget(isNoData ? m_pImportGuideWidget : m_pContentWidget);
}

void CompView::selectAllState() {
    CompPresenter *prst = dynamic_cast<CompPresenter *>(presenter());
    if (!prst->datas().isEmpty()) {
        for (auto data : prst->datas()) {
            if (!data.is_checked) {
                m_pColumnFileNameCkb->setChecked(false);
                return;
            }
        }
        m_pColumnFileNameCkb->setChecked(true);
    } else {
        m_pColumnFileNameCkb->setChecked(false);
    }
}

void CompView::initOutputFormatCbbItem() {
    blockSignalsFunc(m_pOutputFormatCbb, [&]() {
        m_pOutputFormatCbb->clear();
        m_pOutputFormatCbb->addItems(COMP_OUT_FORMATS.values());
        m_pOutputFormatCbb->setCurrentIndex(COMP_OUT_FORMATS.keys().indexOf(SETTINGS->getCompSetting()->getOutFmt()));
    });
}

void CompView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->getCompSetting()->getOutPath());
    m_pOutputFolderCbb->addItem("...");
}

void CompView::setOutputFolder(const QString &path) {
    SETTINGS->getCompSetting()->setOutPath(path);
    m_pOutputFolderCbb->setItemText(0, path);
}

void CompView::setStartAllBtnVisible(bool visible) {
    m_pStartAllBtn->setVisible(visible);
    m_pCancelAllBtn->setVisible(!visible);
}

QList<SImageData> CompView::getListViewModels() const {
    QList<SImageData> datas;
    for (int i = 0; i < m_pListView->model()->rowCount(); ++i) {
        auto index = m_pListView->model()->index(i, 0);
        auto data = index.data(Qt::UserRole).value<SImageData>();
        datas.append(data);
    }
    return datas;
}

SImageData CompView::getListViewModel(const QString &filePath) const {
    for (int i = 0; i < m_pListView->model()->rowCount(); ++i) {
        auto index = m_pListView->model()->index(i, 0);
        auto data = index.data(Qt::UserRole).value<SImageData>();
        if (data.file_path == filePath) {
            return data;
        }
    }
    return SImageData();
}

int CompView::getListViewModelIndex(const QString &filePath) const {
    for (int i = 0; i < m_pListView->model()->rowCount(); ++i) {
        auto index = m_pListView->model()->index(i, 0);
        auto data = index.data(Qt::UserRole).value<SImageData>();
        if (data.file_path == filePath) {
            return i;
        }
    }
    return -1;
}

void CompView::startAllTask() {
    auto func = [this](AsyncTask<void*, void*> *task) -> TaskResult<void*> {
        CompPresenter *prst = dynamic_cast<CompPresenter *>(presenter());
        EasyPhotoCore::Comp::Task cmpTask;
        for (auto data : prst->datas()) {
            if(m_pStartAllBtn->isVisible()) {
                return TaskResult<void*>::Success(nullptr);
            }
            if (data.is_checked) {
                data.state = EImageState_Loading; 
                data.output_size = data.intput_size;
                prst->updateData(data.file_path, data);
                m_pListView->changeData(getListViewModelIndex(data.file_path), data);

                QFileInfo fileInfo = File::fileInfo(data.file_path);
                QString outSuffix = SETTINGS->getCompSetting()->getOutFmt() == Default::Comp::outFormat ? fileInfo.completeSuffix() : SETTINGS->getCompSetting()->getOutFmt();
                auto result = cmpTask.exec(EasyPhotoCore::Comp::SParam{
                    data.file_path.toStdString(),
                    SETTINGS->getCompSetting()->getOutPath().toStdString(),
                    outSuffix.toStdString(),
                    SETTINGS->getCompSetting()->getQuality()});
                    
                data.state = result.success ?  EImageState_Success : EImageState_Fail; 
                data.output_size = QString("%1 MB").arg(QString::number(result.output_size / 1024.0 / 1024.0, 'f', 2));
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

void CompView::startTask(const QString &path) {
    auto func = [this, path](AsyncTask<void*, void*> *task) -> TaskResult<void*> {
        CompPresenter *prst = dynamic_cast<CompPresenter *>(presenter());
        EasyPhotoCore::Comp::Task cmpTask;
        for (auto data : prst->datas()) {
            if (data.file_path == path && data.state != EImageState_Loading) {
                data.state = EImageState_Loading; 
                data.output_size = data.intput_size;
                prst->updateData(data.file_path, data);
                m_pListView->changeData(getListViewModelIndex(data.file_path), data);

                QFileInfo fileInfo = File::fileInfo(data.file_path);
                QString outSuffix = SETTINGS->getCompSetting()->getOutFmt() == Default::Comp::outFormat ? fileInfo.completeSuffix() : SETTINGS->getCompSetting()->getOutFmt();
                auto result = cmpTask.exec(EasyPhotoCore::Comp::SParam {
                    data.file_path.toStdString(),
                    SETTINGS->getCompSetting()->getOutPath().toStdString(),
                    outSuffix.toStdString(),
                    SETTINGS->getCompSetting()->getQuality()});

                data.state = result.success ?  EImageState_Success : EImageState_Fail; 
                data.output_size = QString("%1 MB").arg(QString::number(result.output_size / 1024.0 / 1024.0, 'f', 2));
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

void CompView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Compressor"));
    m_pOutputFormatLbl->setText(tr("Output format:"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pCompreToLbl->setText(tr("Compress All to:"));
    m_pComprePercentLbl->setText(tr("%"));
    m_pStartAllBtn->setText(tr("Compress All"));
    m_pCancelAllBtn->setText(tr("Cancel All"));

    m_pColumnFileNameCkb->setText(tr("File Name"));
    m_pColumnResolutionLbl->setText(tr("Resolution"));
    m_pColumnSizeLbl->setText(tr("Size"));
    m_pColumnStatusLbl->setText(tr("Status"));
    m_pColumnActionLbl->setText(tr("Action"));
}

void CompView::onAddFileBtnClicked() {
    QString title = tr("Open");
    QString directory = SETTINGS->getCompSetting()->getLastAddFilePath();
    QStringList filePaths = QFileDialog::getOpenFileNames(this, title, directory, "All Files (*)");
    if (!filePaths.isEmpty()) {
        QFileInfo fileInfo(filePaths.first());
        QString lastDirectory = fileInfo.absolutePath();
        SETTINGS->getCompSetting()->setLastAddFilePath(lastDirectory);
        listViewImportFile(filePaths);
    }
}

void CompView::onAddFolderBtnClicked() {
    QString title = tr("Select Folder");
    QString folderPath = QFileDialog::getExistingDirectory(this, title, SETTINGS->getCompSetting()->getLastAddFolderPath());
    if (!folderPath.isEmpty()) {
        SETTINGS->getCompSetting()->setLastAddFolderPath(folderPath);
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

void CompView::onClearFileBtnClicked() {
    CompPresenter *prst = dynamic_cast<CompPresenter *>(presenter());
    prst->clearData();
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
}

void CompView::onSelectAllStateChanged(int state) {
    CompPresenter *prst = dynamic_cast<CompPresenter *>(presenter());
    prst->checkedAllData(state);
    m_pListView->changeData(prst->datas());
}

void CompView::onListViewClicked(const QModelIndex &index) {
    auto data = index.data(Qt::UserRole).value<SImageData>();
    QRect rc = m_pListView->visualRect(index);
    int posx = m_pListView->mapFromGlobal(QCursor::pos()).x();
    int posy = m_pListView->mapFromGlobal(QCursor::pos()).y();
    auto bgRect = rc.adjusted(0, 0, 0, 0);
    auto checkedRect = compListCheckedRect(bgRect);
    auto delRect = compListDelRect(bgRect);
    auto compRect = compListConvRect(bgRect);
    if (posx >= delRect.x() && posx <= delRect.x() + delRect.width()
        && posy >= delRect.y() && posy <= delRect.y() + delRect.height()) {
        listItemDelete(data.file_path);
    }
    if (posx >= checkedRect.x() && posx <= checkedRect.x() + checkedRect.width()
        && posy >= checkedRect.y() && posy <= checkedRect.y() + checkedRect.height()) {
        listItemSelectChanged(data.file_path);
    }
    if (posx >= compRect.x() && posx <= compRect.x() + compRect.width()
        && posy >= compRect.y() && posy <= compRect.y() + compRect.height()) {
        startTask(data.file_path);
    }
}

void CompView::onOutputFormatCbbCurrentIndex(int index) {
    QString format = COMP_OUT_FORMATS.keys()[index];
    SETTINGS->getCompSetting()->setOutFmt(format);
    CompPresenter *prst = dynamic_cast<CompPresenter *>(presenter());
    for (auto &data : prst->datas()) {
        data.output_format = format; 
        prst->updateData(data.file_path, data);
    }
    m_pListView->changeData(prst->datas());
}

void CompView::onOutputFolderCbbIndexChanged(int index) {
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

void CompView::onOpenOutputFolderBtnClicked() {
    QString folderPath = SETTINGS->getCompSetting()->getOutPath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
}

void CompView::onStartAllBtnClicked() {
    setStartAllBtnVisible(false);
    startAllTask();
}

void CompView::onCancelAllBtnClicked() {
    setStartAllBtnVisible(true);
}

void CompView::onCompreSliderValueChanged(int value) {
    m_pCompreValueEdit->setText(QString::number(value));
    SETTINGS->getCompSetting()->setQuality(value);
}

void CompView::onCompreValueEdited(const QString &text) {
    int value = text.toInt();
    if (value < 1) value = 1;
    else if (value > 100) value = 100;
    m_pCompreValueEdit->setText(QString::number(value));
    m_pCompreSlider->setValue(value);
    SETTINGS->getCompSetting()->setQuality(value);
}