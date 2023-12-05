/*
 * @Author: weick
 * @Date: 2023-12-05 23:03:26
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:03:26
 */

#include "inc/imagefuncmodel.h"

ImageFuncModel::ImageFuncModel(QObject *parent) :
    QAbstractItemModel(parent) {
}

void ImageFuncModel::changeData(const QList<ImageFunc> &datas) {
    beginResetModel();
    m_Datas.append(datas);
    endResetModel();
}

void ImageFuncModel::changeData(int row, const ImageFunc &data) {
    beginResetModel();
    m_Datas.insert(row, data);
    endResetModel();
}

void ImageFuncModel::addData(QList<ImageFunc> &datas) {
    m_Datas.append(datas);
}

int ImageFuncModel::rowCount(const QModelIndex &parent) const {
    return m_Datas.size();
}

QVariant ImageFuncModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole) {
        // if (index.column() == 0)
        //     return m_Funcs[index.row()].firstname();
        // if (index.column() == 1)
        //     return m_Funcs[index.row()].lastname();
        // if (index.column() == 2)
        //     return m_Funcs[index.row()].birthday();
    }
    return QVariant();
}
