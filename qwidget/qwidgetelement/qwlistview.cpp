#include "qwlistview.h"

QWListView::QWListView(QWidget *parent) : QListView(parent)
{
}

QWListView::~QWListView()
{
}

//
QWListModel::QWListModel(QObject *parent) : QAbstractItemModel(parent)
{
}

QWListModel::~QWListModel()
{
}

//
QWListDelete::QWListDelete(QObject *parent) : QStyledItemDelegate(parent)
{
}

QWListDelete::~QWListDelete()
{
}

void QWListDelete::paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_ASSERT(index.isValid());
}

QSize QWListDelete::sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    return m_size;
}

void QWListDelete::setSize(QSize size)
{
    m_size = size;
}
