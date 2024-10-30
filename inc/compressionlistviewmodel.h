#pragma once
#include "models.h"
#include <QAbstractListModel>

namespace imagecompression {
class CompressionListViewModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit CompressionListViewModel(QObject *parent = 0);
    void changeModels(const QList<Data> &datas);
    void changeData(int row, const Data &data);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

protected:
    QList<Data> m_Datas;
};
} // namespace imagecompression