#pragma once
#include <QWidget>
#include <QListView>
#include <QAbstractItemModel>
#include <QStyledItemDelegate>

class AListView : public QListView
{
    Q_OBJECT
public:
    AListView(QWidget* parent = nullptr);
    ~AListView();
};

class AListModel : public QAbstractItemModel
{
public:
    AListModel(QObject* parent = nullptr);
    ~AListModel();
};

class AListDelegate : public QStyledItemDelegate
{
public:
    AListDelegate(QObject* parent = nullptr);
    ~AListDelegate();
    void paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    void setSize(QSize size);

private:
    QSize m_size = QSize(1, 1);
};
