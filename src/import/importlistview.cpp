#include "import/importlistview.h"
#include "import/importlistpresenter.h"
#include "import/importmodel.h"

#include <QFileDialog>
#include <QStandardPaths>

ImportListView::ImportListView(QWidget *parent, QString fileFilter) :
    QWidget(parent),
    m_FileFilter(fileFilter) {
    createUi();
    connectSig();
}

void ImportListView::importFile(const QStringList &filePaths) {
    ImportListPresenter *prst = dynamic_cast<ImportListPresenter *>(presenter());
    prst->appendData(filePaths);
    m_pImportListView->changeData(prst->getDatas());
    emit sigImportListCountChange(prst->getDatas().count());
    setImportListCurrentIndex(getImportListCount() - 1);
}

void ImportListView::deleteFile(const QString &filePath) {
    ImportListPresenter *prst = dynamic_cast<ImportListPresenter *>(presenter());
    QStringList filePaths;
    filePaths.append(filePath);
    prst->deleteData(filePaths);
    m_pImportListView->changeData(prst->getDatas());
    emit sigImportListCountChange(prst->getDatas().count());
}

void ImportListView::clearFile() {
    ImportListPresenter *prst = dynamic_cast<ImportListPresenter *>(presenter());
    prst->clearData();
    m_pImportListView->changeData(prst->getDatas());
    emit sigImportListCountChange(0);
}

void ImportListView::setImportListCurrentIndex(int index) {
    QModelIndex modelIndex = m_pImportListView->model()->index(index, 0);
    m_pImportListView->setCurrentIndex(modelIndex);
}

int ImportListView::getImportListCount() {
    ImportListPresenter *prst = dynamic_cast<ImportListPresenter *>(presenter());
    return prst->getDatas().count();
}

void ImportListView::createUi() {
    setObjectName("ImportListView");
    setAttribute(Qt::WA_StyledBackground);
    setFixedHeight(120);

    m_pImportListView = new ListView<SImportListItem>(this);
    m_pImportListView->setViewMode(QListView::ListMode);
    m_pImportListView->setResizeMode(QListView::Adjust);
    m_pImportListView->setFlow(QListView::LeftToRight);
    m_pImportListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_pImportListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pImportListView->setSpacing(8);
    m_pImportListDelegate = new ImportListDelegate(m_pImportListView);
    m_pImportListView->setItemDelegate(m_pImportListDelegate);
    m_pImportListView->viewport()->installEventFilter(m_pImportListDelegate);

    m_pAddBtn = new IconButton(this);
    m_pAddBtn->setFixedSize(24, 24);
    m_pAddBtn->setIconSize(24, 24);
    m_pAddBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/old/icon/icon_state/icon24/icon24_file.png");

    m_pClearBtn = new IconButton(this);
    m_pClearBtn->setFixedSize(24, 24);
    m_pClearBtn->setIconSize(24, 24);
    m_pClearBtn->setFourPixmapPath(":/qtmaterial/img/vcu/dark/old/icon/icon_state/icon24/icon24_file.png");

    auto btnLayout = new QVBoxLayout();
    btnLayout->setContentsMargins(0, 8, 0, 8);
    btnLayout->setSpacing(0);
    btnLayout->addWidget(m_pAddBtn);
    btnLayout->addStretch();
    btnLayout->addWidget(m_pClearBtn);

    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(8);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(m_pImportListView, 1);
}

void ImportListView::connectSig() {
    connect(m_pAddBtn, &IconButton::clicked, this, &ImportListView::onAddBtnClicked);
    connect(m_pClearBtn, &IconButton::clicked, this, &ImportListView::onClearBtnClicked);
    connect(m_pImportListView, &QListView::clicked, this, &ImportListView::onListViewClicked);
    connect(m_pImportListView, &AbstractListView::sigCurrentChanged, this, &ImportListView::onListViewCurrentChanged);
}

void ImportListView::listItemDelete(const QString &filePath) {
    ImportListPresenter *prst = dynamic_cast<ImportListPresenter *>(presenter());
    QStringList filePaths;
    filePaths.append(filePath);
    prst->deleteData(filePaths);
    m_pImportListView->changeData(prst->getDatas());
    emit sigImportListCountChange(prst->getDatas().count());
}

void ImportListView::onAddBtnClicked() {
    QString title = tr("Open");
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString filter = tr("image files");
    QStringList filePaths = QFileDialog::getOpenFileNames(this, title, directory, QString("%1 %2").arg(filter).arg(m_FileFilter));
    if (!filePaths.isEmpty()) {
        importFile(filePaths);
    }
}

void ImportListView::onClearBtnClicked() {
    clearFile();
}

void ImportListView::onListViewClicked(const QModelIndex &index) {
    auto data = index.data(Qt::UserRole).value<SImportListItem>();
    QRect rc = m_pImportListView->visualRect(index);
    int posx = m_pImportListView->mapFromGlobal(QCursor::pos()).x();
    int posy = m_pImportListView->mapFromGlobal(QCursor::pos()).y();
    auto bgRect = rc.adjusted(0, 0, 0, 0);
    auto delRect = QRect(bgRect.right() - 4 - 16, bgRect.y() + 4, 16, 16);
    if (posx >= delRect.x() && posx <= delRect.x() + delRect.width()
        && posy >= delRect.y() && posy <= delRect.y() + delRect.height()) {
        listItemDelete(data.path);
    }
}

void ImportListView::onListViewCurrentChanged(const QModelIndex &current, const QModelIndex &previous) {
    auto data = current.data(Qt::UserRole).value<SImportListItem>();
    emit sigImportListCurrentChanged(data.path);
}