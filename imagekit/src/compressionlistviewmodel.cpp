/*
 * @Author: weick
 * @Date: 2023-12-11 23:06:34
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 22:10:49
 */

#include "inc/compressionlistviewmodel.h"

CompressionListViewModel::CompressionListViewModel(QObject *parent) {
}
void CompressionListViewModel::changeModels(const QList<imagecompression::Data> &datas) {
    beginResetModel();
    m_Datas = datas;
    endResetModel();
}
void CompressionListViewModel::changeData(int row, const imagecompression::Data &data) {
    beginResetModel();
    m_Datas[row] = data;
    endResetModel();
}
int CompressionListViewModel::rowCount(const QModelIndex &parent) const {
    return m_Datas.count();
}
QVariant CompressionListViewModel::data(const QModelIndex &index, int role) const {
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
