/*
 * @Author: weick
 * @Date: 2024-03-28 07:49:56
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-28 08:16:11
 */

#pragma once
#include <QAbstractListModel>

template <typename T>
class AListViewModel : public QAbstractListModel {
public:
    AListViewModel(QObject *parent) {
    }

    void changeModels(const QList<T> &datas) {
        beginResetModel();
        datas_ = datas;
        endResetModel();
    }

    void changeData(int row, const T &data) {
        beginResetModel();
        datas_[row] = data;
        endResetModel();
    }

    int rowCount(const QModelIndex &parent) const {
        return datas_.count();
    }

    QVariant data(const QModelIndex &index, int role) const {
        if (!index.isValid()) {
            return QVariant();
        }
        if (index.row() >= datas_.size()) {
            return QVariant();
        }
        if (role == Qt::UserRole) {
            return QVariant::fromValue(datas_[index.row()]);
        }
        return QVariant();
    }

    Qt::ItemFlags flags(const QModelIndex &index) const {
        if (!index.isValid())
            return Qt::NoItemFlags;
        return Qt::ItemIsEditable | QAbstractListModel::flags(index);
    }
protected:
    QList<T> datas_;
};