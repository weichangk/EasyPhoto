#include "home/view.h"
#include "home/presenter.h"
#include "funcchangemessage.h"
#include "NavbarCheckedMessage.h"

#include <QScrollBar>

HomeView::HomeView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void HomeView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    initListView();
}

void HomeView::createUi() {
    setObjectName("HomeView");
    setAttribute(Qt::WA_StyledBackground);

    m_pListView = new ListView<SFuncItemData>(this);
    m_pListView->setSpacing(24);
    m_pListDelegate = new FuncItemDelegate(m_pListView);
    m_pListView->setItemDelegate(m_pListDelegate);
    m_pListView->viewport()->installEventFilter(m_pListDelegate);
    m_pListView->verticalScrollBar()->setObjectName("HomeViewScrollBar");
    m_pListView->verticalScrollBar()->setStyle(m_pListView->verticalScrollBar()->style());

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(48, 16, 2, 16);
    layout->setSpacing(0);
    layout->addWidget(m_pListView, 1);
}

void HomeView::connectSig() {
    connect(m_pListView, &QListView::clicked, this, &HomeView::onListViewClicked);
}

void HomeView::initListView() {
    HomePresenter *prst = dynamic_cast<HomePresenter *>(presenter());
    m_pListView->changeData(prst->datas());
}

void HomeView::funcChange(int func) {
    FuncChangeMessage msg(func);
    presenter()->sendMessage(&msg);
}

void HomeView::navbarChecked(int func) {
    NavbarCheckedMessage msg(func);
    presenter()->sendMessage(&msg);
}

void HomeView::onListViewClicked(const QModelIndex &index) {
    auto data = index.data(Qt::UserRole).value<SFuncItemData>();
    QRect rc = m_pListView->visualRect(index);
    int posx = m_pListView->mapFromGlobal(QCursor::pos()).x();
    int posy = m_pListView->mapFromGlobal(QCursor::pos()).y();
    auto bgRect = rc.adjusted(0, 0, -8, -8);
    auto checkedRect = QRect(bgRect.x() + 4, bgRect.y() + 4, 16, 16);
    auto delRect = QRect(bgRect.right() - 4 - 16, bgRect.y() + 4, 16, 16);
    if (posx >= delRect.x() && posx <= delRect.x() + delRect.width()
        && posy >= delRect.y() && posy <= delRect.y() + delRect.height()) {
    }
    if (posx >= checkedRect.x() && posx <= checkedRect.x() + checkedRect.width()
        && posy >= checkedRect.y() && posy <= checkedRect.y() + checkedRect.height()) {
    }
    funcChange(data.func);
    navbarChecked(data.func);
}