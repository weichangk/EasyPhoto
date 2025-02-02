#include "conversion/view.h"
#include "conversion/presenter.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>

OutputFormatView::OutputFormatView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void OutputFormatView::createUi() {
    setObjectName("OutputFormatView");
    setAttribute(Qt::WA_StyledBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(478, 272);

    auto popup = new PopupWindow(this);
    auto mask = new MaskWidget(this);
    mask->setPramas(MaskWidget::RoundType::Round_All, 0, 8, 8);

    m_pListView = new ListView<SOuputFormat>(this);
    m_pListView->setSpacing(0);
    m_pListDelegate = new OutputFormatDelegate(m_pListView);
    m_pListView->setItemDelegate(m_pListDelegate);
    m_pListView->viewport()->installEventFilter(m_pListDelegate);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(0);
    layout->addWidget(m_pListView, 1);
}

void OutputFormatView::connectSig() {
}

ComboBoxFilter::ComboBoxFilter(QObject *parent) : QObject(parent) {
}

bool ComboBoxFilter::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        emit sigClicked();
    }
    return QObject::eventFilter(watched, event);
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

void ConversionView::createUi() {
    setObjectName("ConversionView");
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

    m_pOutputFormatCbbFilter = new ComboBoxFilter(m_pOutputFormatCbb);
    m_pOutputFormatCbb->installEventFilter(m_pOutputFormatCbbFilter);

    m_pOutputFolderLbl = new QLabel(bottomWidget);

    m_pOutputFolderCbb = new QComboBox(bottomWidget);
    m_pOutputFolderCbb->setFixedWidth(120);

    m_pOutputFolderCbbFilter = new ComboBoxFilter(m_pOutputFolderCbb);
    m_pOutputFolderCbb->installEventFilter(m_pOutputFolderCbbFilter);

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

    m_pListView = new ListView<Data>(this);
    m_pListView->setSpacing(0);
    m_pListDelegate = new ListDelegate(m_pListView);
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
}

QWidget *ConversionView::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("ConversionView_DividingLine");
    dividingLine->setFixedHeight(1);
    return dividingLine;
}

void ConversionView::listViewImportFile(const QStringList filePaths) {
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
    }
}

void ConversionView::listItemSelectChanged(const QString filePath) {
    ConversionPresenter *prst = dynamic_cast<ConversionPresenter *>(presenter());
    prst->switchCheckedData(filePath);
    m_pListView->changeData(prst->datas());
    selectAllState();
}

void ConversionView::listItemDelete(const QString filePath) {
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
    m_pStackedLayout->setCurrentWidget(isNoData ? m_pImportGuideWidget : m_pListView);
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
    if(!m_pOutputFormatView) {
        m_pOutputFormatView = new OutputFormatView(this);
    }

    auto btnPos = m_pOutputFormatCbb->mapToGlobal(QPoint(0, 0));
    auto pos = btnPos - QPoint(0, m_pOutputFormatView->height() + 8);

    m_pOutputFormatView->move(pos);
    m_pOutputFormatView->show();
}

void ConversionView::onLanguageChange() {
    m_pSelectAllCkb->setText(tr("Select All"));
    m_pOutputFormatLbl->setText(tr("Output format:"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pConversionBtn->setText(tr("Conversion"));
}

void ConversionView::onAddFileBtnClicked() {
    QString title = tr("Open");
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QStringList filePaths = QFileDialog::getOpenFileNames(this, title, directory, "All Files (*)");
    if (!filePaths.isEmpty()) {
        listViewImportFile(filePaths);
    }
}

void ConversionView::onAddFolderBtnClicked() {
    QString title = tr("Select Folder");
    QString folderPath = QFileDialog::getExistingDirectory(nullptr, title, QDir::homePath());
    if (!folderPath.isEmpty()) {
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
    auto data = index.data(Qt::UserRole).value<Data>();
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

void ConversionView::onOutputFormatCbbClicked() {
    showOutputFormatView();
}

void ConversionView::onOutputFolderCbbClicked() {
}