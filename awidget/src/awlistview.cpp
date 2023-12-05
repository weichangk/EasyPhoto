/*
 * @Author: weick
 * @Date: 2023-12-05 23:00:38
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:00:38
 */

#include "inc/awlistview.h"

AListView::AListView(QWidget *parent) :
    QListView(parent) {
}

AListView::~AListView() {
}

//
AListModel::AListModel(QObject *parent) :
    QAbstractItemModel(parent) {
}

AListModel::~AListModel() {
}

//
AListDelegate::AListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

AListDelegate::~AListDelegate() {
}

void AListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_ASSERT(index.isValid());
}

QSize AListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return m_size;
}

void AListDelegate::setSize(QSize size) {
    m_size = size;
}
