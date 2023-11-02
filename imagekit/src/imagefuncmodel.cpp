#include "inc/imagefuncmodel.h"

ImageFuncModel::ImageFuncModel(QObject *parent) : QAbstractItemModel(parent)
{
}

int ImageFuncModel::rowCount(const QModelIndex &parent) const
{
    return m_Funcs.size();
}
int ImageFuncModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant ImageFuncModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole)
    {
        // if (index.column() == 0)
        //     return m_Funcs[index.row()].firstname();
        // if (index.column() == 1)
        //     return m_Funcs[index.row()].lastname();
        // if (index.column() == 2)
        //     return m_Funcs[index.row()].birthday();
    }
    return QVariant();
}

void ImageFuncModel::append(ImageFunc func)
{
    beginResetModel();
    m_Funcs.append(func);
    endResetModel();
}

void ImageFuncModel::clear()
{
    beginResetModel();
    m_Funcs.clear();
    endResetModel();
}
