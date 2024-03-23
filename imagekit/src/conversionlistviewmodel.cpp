/*
 * @Author: weick
 * @Date: 2023-12-11 23:06:34
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 23:06:54
 */

#include "inc/conversionlistviewmodel.h"
#include "inc/models.h"

ConversionListViewModel::ConversionListViewModel(QObject *parent) {
}
void ConversionListViewModel::changeModels(const QList<imageconversion::Data> &datas) {
    beginResetModel();
    m_Datas = datas;
    endResetModel();
}
void ConversionListViewModel::changeData(int row, const imageconversion::Data &data) {
    beginResetModel();
    m_Datas[row] = data;
    endResetModel();
}
int ConversionListViewModel::rowCount(const QModelIndex &parent) const {
    return m_Datas.count();
}
QVariant ConversionListViewModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= m_Datas.size()) {
        return QVariant();
    }
    if (role == Qt::UserRole) {
        return QVariant::fromValue(m_Datas[index.row()]);
    }
    return QVariant();
}
