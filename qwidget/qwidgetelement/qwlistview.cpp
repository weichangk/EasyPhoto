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
