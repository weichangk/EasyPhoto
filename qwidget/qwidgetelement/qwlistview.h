#pragma once
#include <QWidget>
#include <QListView>
#include <QAbstractItemModel>
#include <QStyledItemDelegate>

class QWListView : public QListView
{
public:
    QWListView(QWidget* parent = nullptr);
    ~QWListView();
};

class QWListModel : public QAbstractItemModel
{
    QWListModel(QObject* parent = nullptr);
    ~QWListModel();
};

class QWListDelete : public QStyledItemDelegate
{
    QWListDelete(QObject* parent = nullptr);
    ~QWListDelete();
};
