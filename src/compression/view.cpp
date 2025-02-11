#include "compression/view.h"
#include "compression/presenter.h"
#include "settings.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>

CompressionOutputFormatView::CompressionOutputFormatView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void CompressionOutputFormatView::setSelection(const QString &format) {
    for (int row = 0; row < m_pListView->count(); ++row) {
        auto data = m_pListView->data(row);
        if (data.name == format) {
            QModelIndex index = m_pListView->index(row);
            m_pListView->setCurrentIndex(index);
        }
    }
}

void CompressionOutputFormatView::createUi() {
    setObjectName("CompressionOutputFormatView");
    setAttribute(Qt::WA_StyledBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(281, 152);

    auto popup = new PopupWindow(this);
    auto mask = new MaskWidget(this);
    mask->setPramas(MaskWidget::RoundType::Round_All, 0, 8, 8);

    m_pListView = new ListView<SCompressionOuputFormat>(this);
    m_pListView->setSpacing(0);
    m_pListDelegate = new CompressionOutputFormatDelegate(m_pListView);
    m_pListView->setItemDelegate(m_pListDelegate);
    m_pListView->viewport()->installEventFilter(m_pListDelegate);
    m_pListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QString format = COMP_OUT_FORMATS;
    QStringList formats = format.split(' ');
    QList<SCompressionOuputFormat> formatDatas;
    for (auto &item : formats) {
        SCompressionOuputFormat format = {item, item.toUpper(), nullptr, false};
        formatDatas.append(format);
    }
    m_pListView->changeData(formatDatas);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_pListView, 1);
}

void CompressionOutputFormatView::connectSig() {
    connect(m_pListView, &QListView::clicked, this, &CompressionOutputFormatView::onListItemViewclicked);
}

void CompressionOutputFormatView::onListItemViewclicked(const QModelIndex &index) {
    auto data = m_pListView->data(index);
    SETTINGS->setCompressionOutFormat(data.name);
    emit sigSelectionChanged(data.name);
    close();
}

CompressionView::CompressionView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

void CompressionView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    listViewNoDataState();
    selectAllState();
}

void CompressionView::createUi() {
    setObjectName("CompressionView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    QFont iconFont = Font::getIconFont(":/font/iconfont.ttf");

    QWidget *topWidget = new QWidget(this);
    topWidget->setFixedHeight(56);

    m_pAddFileBtn = new VectorButton(topWidget);
    m_pAddFileBtn->setObjectName("VectorButton_HW28_I20");
    m_pAddFileBtn->setFont(iconFont);
    m_pAddFileBtn->setText(QChar(0xe634));

    m_pAddFolderBtn = new VectorButton(topWidget);
    m_pAddFolderBtn->setObjectName("VectorButton_HW28_I20");
    m_pAddFolderBtn->setFont(iconFont);
    m_pAddFolderBtn->setText(QChar(0xe634));

    m_pClearFileBtn = new VectorButton(topWidget);
    m_pClearFileBtn->setObjectName("VectorButton_HW28_I20");
    m_pClearFileBtn->setFont(iconFont);
    m_pClearFileBtn->setText(QChar(0xe634));

    m_pSelectAllCkb = new QCheckBox(topWidget);

    m_pListModeSwitchBtn = new VectorButton(topWidget);
    m_pListModeSwitchBtn->setObjectName("VectorButton_HW28_I20");
    m_pListModeSwitchBtn->setFont(iconFont);
    m_pListModeSwitchBtn->setText(QChar(0xe634));

    auto topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setContentsMargins(20, 0, 20, 0);
    topWidgetLayout->setSpacing(8);
    topWidgetLayout->addWidget(m_pAddFileBtn, Qt::AlignVCenter);
    topWidgetLayout->addWidget(m_pAddFolderBtn, Qt::AlignVCenter);
    topWidgetLayout->addWidget(m_pClearFileBtn, Qt::AlignVCenter);
    topWidgetLayout->addWidget(m_pSelectAllCkb, Qt::AlignVCenter);
    topWidgetLayout->addStretch();
    topWidgetLayout->addWidget(m_pListModeSwitchBtn, Qt::AlignVCenter);

    QWidget *bottomWidget = new QWidget(this);
    bottomWidget->setFixedHeight(80);

    m_pOutputFormatLbl = new QLabel(bottomWidget);

    m_pOutputFormatCbb = new QComboBox(bottomWidget);
    m_pOutputFormatCbb->setFixedWidth(120);

    m_pOutputFormatEdit = new QLineEdit(m_pOutputFormatCbb);
    m_pOutputFormatEdit->setReadOnly(true);
    m_pOutputFormatCbb->setLineEdit(m_pOutputFormatEdit);

    setOutputFormatCbbText(SETTINGS->compressionOutFormat());

    m_pOutputFormatCbbFilter = new ComboBoxFilter(m_pOutputFormatCbb);
    m_pOutputFormatCbb->installEventFilter(m_pOutputFormatCbbFilter);

    m_pOutputFolderLbl = new QLabel(bottomWidget);

    m_pOutputFolderCbb = new QComboBox(bottomWidget);
    m_pOutputFolderCbb->setFixedWidth(120);

    m_pOutputFolderCbbFilter = new ComboBoxFilter(m_pOutputFolderCbb);
    m_pOutputFolderCbb->installEventFilter(m_pOutputFolderCbbFilter);

    initOutputFolderCbbItem();

    m_pOpenOutputFolderBtn = new VectorButton(bottomWidget);
    m_pOpenOutputFolderBtn->setObjectName("VectorButton_HW28_I20");
    m_pOpenOutputFolderBtn->setFont(iconFont);
    m_pOpenOutputFolderBtn->setText(QChar(0xe634));

    m_pConversionBtn = new QPushButton(bottomWidget);

    auto bottomWidgetLayout = new QHBoxLayout(bottomWidget);
    bottomWidgetLayout->setContentsMargins(20, 0, 20, 0);
    bottomWidgetLayout->setSpacing(0);
    bottomWidgetLayout->addWidget(m_pOutputFormatLbl, Qt::AlignVCenter);
    bottomWidgetLayout->addWidget(m_pOutputFormatCbb, Qt::AlignVCenter);
    bottomWidgetLayout->addWidget(m_pOutputFolderLbl, Qt::AlignVCenter);
    bottomWidgetLayout->addWidget(m_pOutputFolderCbb, Qt::AlignVCenter);
    bottomWidgetLayout->addWidget(m_pOpenOutputFolderBtn, Qt::AlignVCenter);
    bottomWidgetLayout->addStretch();
    bottomWidgetLayout->addWidget(m_pConversionBtn, Qt::AlignVCenter);

    m_pImportGuide = new ImportGuide(this);
    m_pImportGuideWidget = new QWidget(this);
    QVBoxLayout *importGuideLayout = new QVBoxLayout(m_pImportGuideWidget);
    importGuideLayout->setAlignment(Qt::AlignCenter);
    importGuideLayout->addWidget(m_pImportGuide);

    m_pListView = new ListView<SCompressionData>(this);
    m_pListView->setSpacing(0);
    m_pListDelegate = new CompressionListDelegate(m_pListView);
    m_pListView->setItemDelegate(m_pListDelegate);
    m_pListView->viewport()->installEventFilter(m_pListDelegate);

    m_pStackedLayout = new QStackedLayout();
    m_pStackedLayout->addWidget(m_pImportGuideWidget);
    m_pStackedLayout->addWidget(m_pListView);
    auto stackedMarginLayout = new QVBoxLayout();
    stackedMarginLayout->setContentsMargins(8, 8, 2, 8);
    stackedMarginLayout->addLayout(m_pStackedLayout, 1);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(topWidget);
    layout->addWidget(createDividingLine());
    layout->addLayout(stackedMarginLayout, 1);
    layout->addWidget(createDividingLine());
    layout->addWidget(bottomWidget);
}

void CompressionView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &CompressionView::onLanguageChange);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &CompressionView::listViewImportFile);
    connect(m_pAddFileBtn, &QPushButton::clicked, this, &CompressionView::onAddFileBtnClicked);
    connect(m_pAddFolderBtn, &QPushButton::clicked, this, &CompressionView::onAddFolderBtnClicked);
    connect(m_pClearFileBtn, &QPushButton::clicked, this, &CompressionView::onClearFileBtnClicked);
    connect(m_pSelectAllCkb, &QCheckBox::stateChanged, this, &CompressionView::onSelectAllStateChanged);
    connect(m_pListModeSwitchBtn, &QPushButton::clicked, this, &CompressionView::onListModeSwitchBtnClicked);
    connect(m_pListView, &QListView::clicked, this, &CompressionView::onListViewClicked);
    connect(m_pOutputFormatCbbFilter, &ComboBoxFilter::sigClicked, this, &CompressionView::onOutputFormatCbbClicked);
    connect(m_pOutputFolderCbbFilter, &ComboBoxFilter::sigClicked, this, &CompressionView::onOutputFolderCbbClicked);
    connect(m_pOutputFolderCbb, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &CompressionView::onOutputFolderCbbIndexChanged);
    connect(m_pOpenOutputFolderBtn, &QPushButton::clicked, this, &CompressionView::onOpenOutputFolderBtnClicked);
    connect(m_pConversionBtn, &QPushButton::clicked, this, &CompressionView::onConversionBtnClicked);
}

QWidget *CompressionView::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("CompressionView_DividingLine");
    dividingLine->setFixedHeight(1);
    return dividingLine;
}

void CompressionView::listViewImportFile(const QStringList &filePaths) {
    CompressionPresenter *prst = dynamic_cast<CompressionPresenter *>(presenter());
    prst->appendData(filePaths);
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
    selectAllState();
}

void CompressionView::onListModeSwitchBtnClicked() {
    CompressionPresenter *prst = dynamic_cast<CompressionPresenter *>(presenter());
    if (!prst->datas().isEmpty()) {
        m_pListDelegate->setListMode(!m_pListDelegate->isListMode());
        m_pListModeSwitchBtn->setText(m_pListDelegate->isListMode() ? QChar(0xe634) : QChar(0xe634));
        m_pListView->changeData(prst->datas());
    }
}

void CompressionView::listItemSelectChanged(const QString &filePath) {
    CompressionPresenter *prst = dynamic_cast<CompressionPresenter *>(presenter());
    prst->switchCheckedData(filePath);
    m_pListView->changeData(prst->datas());
    blockSignalsFunc(m_pSelectAllCkb, [&]() {
        selectAllState();
    });
}

void CompressionView::listItemDelete(const QString &filePath) {
    CompressionPresenter *prst = dynamic_cast<CompressionPresenter *>(presenter());
    QStringList filePaths;
    filePaths.append(filePath);
    prst->deleteData(filePaths);
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
    selectAllState();
}

void CompressionView::listViewNoDataState() {
    CompressionPresenter *prst = dynamic_cast<CompressionPresenter *>(presenter());
    bool isNoData = prst->datas().isEmpty();
    m_pClearFileBtn->setVisible(!isNoData);
    m_pListModeSwitchBtn->setVisible(!isNoData);
    m_pSelectAllCkb->setVisible(!isNoData);
    m_pStackedLayout->setCurrentWidget(isNoData ? m_pImportGuideWidget : m_pListView);
}

void CompressionView::selectAllState() {
    CompressionPresenter *prst = dynamic_cast<CompressionPresenter *>(presenter());
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

void CompressionView::showOutputFormatView() {
    if (!m_pOutputFormatView) {
        m_pOutputFormatView = new CompressionOutputFormatView(this);
        connect(m_pOutputFormatView, &CompressionOutputFormatView::sigSelectionChanged, this, &CompressionView::setOutputFormatCbbText);
    }

    m_pOutputFormatView->setSelection(SETTINGS->compressionOutFormat());

    auto btnPos = m_pOutputFormatCbb->mapToGlobal(QPoint(0, 0));
    auto pos = btnPos - QPoint(0, m_pOutputFormatView->height() + 8);

    m_pOutputFormatView->move(pos);
    m_pOutputFormatView->show();
}

void CompressionView::setOutputFormatCbbText(const QString &text) {
    m_pOutputFormatEdit->setText(text.toUpper());
}

void CompressionView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->compressionOutPath());
    m_pOutputFolderCbb->addItem("...");
}

void CompressionView::CompressionView::setOutputFolder(const QString &path) {
    SETTINGS->setCompressionOutPath(path);
    m_pOutputFolderCbb->setItemText(0, path);
}

void CompressionView::onLanguageChange() {
    m_pSelectAllCkb->setText(tr("Select All"));
    m_pOutputFormatLbl->setText(tr("Output format:"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pConversionBtn->setText(tr("Conversion"));
}

void CompressionView::onAddFileBtnClicked() {
    QString title = tr("Open");
    QString directory = SETTINGS->compressionLastAddFilePath();
    QStringList filePaths = QFileDialog::getOpenFileNames(this, title, directory, "All Files (*)");
    if (!filePaths.isEmpty()) {
        QFileInfo fileInfo(filePaths.first());
        QString lastDirectory = fileInfo.absolutePath();
        SETTINGS->setCompressionLastAddFilePath(lastDirectory);
        listViewImportFile(filePaths);
    }
}

void CompressionView::onAddFolderBtnClicked() {
    QString title = tr("Select Folder");
    QString folderPath = QFileDialog::getExistingDirectory(this, title, SETTINGS->compressionLastAddFolderPath());
    if (!folderPath.isEmpty()) {
        SETTINGS->setCompressionLastAddFolderPath(folderPath);
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

void CompressionView::onClearFileBtnClicked() {
    CompressionPresenter *prst = dynamic_cast<CompressionPresenter *>(presenter());
    prst->clearData();
    m_pListView->changeData(prst->datas());
    listViewNoDataState();
}

void CompressionView::onSelectAllStateChanged(int state) {
    CompressionPresenter *prst = dynamic_cast<CompressionPresenter *>(presenter());
    prst->checkedAllData(state);
    m_pListView->changeData(prst->datas());
}

void CompressionView::onListViewClicked(const QModelIndex &index) {
    auto data = index.data(Qt::UserRole).value<SCompressionData>();
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

void CompressionView::onOutputFormatCbbClicked() {
    showOutputFormatView();
}

void CompressionView::onOutputFolderCbbClicked() {
}

void CompressionView::onOutputFolderCbbIndexChanged(int index) {
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

void CompressionView::onOpenOutputFolderBtnClicked() {
    QString folderPath = SETTINGS->compressionOutPath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(folderPath));
}

void CompressionView::onConversionBtnClicked() {
    // CompressionPresenter *prst = dynamic_cast<CompressionPresenter *>(presenter());
    // ConversionTask task;
    // for(auto data : prst->datas()) {
    //     if(data.is_checked) {
    //         task.exec(data.file_path, SETTINGS->compressionOutPath(), SETTINGS->compressionOutFormat());
    //     }
    // }
}