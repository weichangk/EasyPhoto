/*
 * @Author: weick
 * @Date: 2023-12-13 23:34:49
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-13 23:36:24
 */

#include "inc/compressionlistview.h"
#include "inc/compressionlistdelegate.h"
#include <QMouseEvent>

CompressionListView::CompressionListView(QWidget *parent) :
    QListView(parent) {
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAttribute(Qt::WA_StyledBackground);
    setResizeMode(QListView::Adjust);
    setViewMode(QListView::IconMode);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setMouseTracking(true);
    setStyleSheet("border:0px; background-color:transparent;");
    setSpacing(0);
    m_Model = new CompressionListViewModel(this);
    setModel(m_Model);
    auto delegate = new CompressionListDelegate(this);
    setItemDelegate(delegate);
    viewport()->installEventFilter(delegate);
}

void CompressionListView::chageData(const CompressionDatas &datas) {
    m_Model->changeModels(datas);
}

CompressionData CompressionListView::data(int i) const {
    return m_Model->data(m_Model->index(i, 0), Qt::UserRole).value<CompressionData>();
}

int CompressionListView::count() const {
    return m_Model->rowCount(QModelIndex());
}

void CompressionListView::mouseMoveEvent(QMouseEvent *event) {
    if (indexAt(event->pos()).row() != -1) {
        setCursor(Qt::PointingHandCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void CompressionListView::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
}
