#include "home/view.h"
#include "home/presenter.h"

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
    layout->setContentsMargins(24, 16, 2, 16);
    layout->setSpacing(0);
    layout->addWidget(m_pListView, 1);
}

void HomeView::connectSig() {
}

void HomeView::initListView() {
    HomePresenter *prst = dynamic_cast<HomePresenter *>(presenter());
    m_pListView->changeData(prst->datas());
}