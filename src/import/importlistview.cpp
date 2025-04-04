#include "import/importlistview.h"

ImportListView::ImportListView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void ImportListView::createUi() {
    setObjectName("ImportListView");
    setAttribute(Qt::WA_StyledBackground);
    setFixedHeight(120);

    m_pImportListView = new ListView<SImportListItem>(this);
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

    auto btnLayout = new QHBoxLayout();
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->setSpacing(0);
    btnLayout->addWidget(m_pAddBtn);
    btnLayout->addStretch();
    btnLayout->addWidget(m_pClearBtn);

    auto mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(8);
    mainLayout->addWidget(m_pImportListView, 1);
    mainLayout->addLayout(btnLayout);
}

void ImportListView::connectSig() {
    connect(m_pAddBtn, &IconButton::clicked, this, &ImportListView::onAddBtnClicked);
    connect(m_pClearBtn, &IconButton::clicked, this, &ImportListView::onClearBtnClicked);
}

void ImportListView::onAddBtnClicked() {
}

void ImportListView::onClearBtnClicked() {
}