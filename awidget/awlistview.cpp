#include "awlistview.h"

AListView::AListView(QWidget *parent) : QListView(parent)
{
}

AListView::~AListView()
{
}

//
AListModel::AListModel(QObject *parent) : QAbstractItemModel(parent)
{
}

AListModel::~AListModel()
{
}

//
AListDelegate::AListDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

AListDelegate::~AListDelegate()
{
}

void AListDelegate::paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_ASSERT(index.isValid());
}

QSize AListDelegate::sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    return m_size;
}

void AListDelegate::setSize(QSize size)
{
    m_size = size;
}
