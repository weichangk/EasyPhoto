/*
 * @Author: weick
 * @Date: 2024-03-28 07:50:57
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-28 08:01:09
 */

#include "inc/alistviewmodel.h"

template <typename T>
AListViewModel<T>::AListViewModel(QObject *parent) {
}

template <typename T>
void AListViewModel<T>::changeModels(const QList<T> &datas) {
    beginResetModel();
    datas_ = datas;
    endResetModel();
}

template <typename T>
void AListViewModel<T>::changeData(int row, const T &data) {
    beginResetModel();
    datas_[row] = data;
    endResetModel();
}

template <typename T>
int AListViewModel<T>::rowCount(const QModelIndex &parent) const {
    return datas_.count();
}

template <typename T>
QVariant AListViewModel<T>::data(const QModelIndex &index, int role) const {
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