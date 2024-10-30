#include "inc/compressionlistviewmodel.h"

namespace imagecompression {
CompressionListViewModel::CompressionListViewModel(QObject *parent) {
}
void CompressionListViewModel::changeModels(const QList<Data> &datas) {
    beginResetModel();
    m_Datas = datas;
    endResetModel();
}
void CompressionListViewModel::changeData(int row, const Data &data) {
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
} // namespace imagecompression