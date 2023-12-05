/*
 * @Author: weick
 * @Date: 2023-12-05 22:58:52
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 22:58:52
 */

#pragma once
#include "awidget_global.h"
#include <QListView>
#include <QStyledItemDelegate>

class AWIDGET_EXPORT AListView : public QListView {
    Q_OBJECT
public:
    AListView(QWidget *parent = nullptr);
    ~AListView();
};

class AListModel : public QAbstractItemModel {
public:
    AListModel(QObject *parent = nullptr);
    ~AListModel();
};

class AListDelegate : public QStyledItemDelegate {
public:
    AListDelegate(QObject *parent = nullptr);
    ~AListDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setSize(QSize size);

private:
    QSize m_size = QSize(1, 1);
};
