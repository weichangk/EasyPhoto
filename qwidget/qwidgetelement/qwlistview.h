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
public:
    QWListModel(QObject* parent = nullptr);
    ~QWListModel();
};

class QWListDelete : public QStyledItemDelegate
{
public:
    QWListDelete(QObject* parent = nullptr);
    ~QWListDelete();
    void paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    void setSize(QSize size);

private:
    QSize m_size = QSize(1, 1);
};
