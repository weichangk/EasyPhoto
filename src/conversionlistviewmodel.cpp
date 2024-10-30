#include "inc/conversionlistviewmodel.h"
#include "inc/models.h"

namespace imageconversion {
ConversionListViewModel::ConversionListViewModel(QObject *parent) {
}
void ConversionListViewModel::changeModels(const QList<Data> &datas) {
    beginResetModel();
    m_Datas = datas;
    endResetModel();
}
void ConversionListViewModel::changeData(int row, const Data &data) {
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
} // namespace imageconversion