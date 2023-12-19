/*
 * @Author: weick
 * @Date: 2023-12-13 23:34:49
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-13 23:36:24
 */

#include "inc/conversionlistview.h"
#include "inc/conversionlistdelegate.h"
#include <QMouseEvent>

ConversionListView::ConversionListView(QWidget *parent) :
    QListView(parent) {
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAttribute(Qt::WA_StyledBackground);
    setResizeMode(QListView::Adjust);
    setViewMode(QListView::IconMode);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setMouseTracking(true);
    setStyleSheet("border:0px; background-color:transparent");
    setSpacing(0);
    m_Model = new ConversionListViewModel(this);
    setModel(m_Model);
    auto delegate = new ConversionListDelegate(this);
    setItemDelegate(delegate);
    viewport()->installEventFilter(delegate);
}

void ConversionListView::chageData(const ConversionDatas &datas) {
    m_Model->changeModels(datas);
}

ConversionData ConversionListView::data(int i) const {
    return m_Model->data(m_Model->index(i, 0), Qt::UserRole).value<ConversionData>();
}

int ConversionListView::count() const {
    return m_Model->rowCount(QModelIndex());
}

void ConversionListView::mouseMoveEvent(QMouseEvent *event) {
    if (indexAt(event->pos()).row() != -1) {
        setCursor(Qt::PointingHandCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void ConversionListView::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
}
