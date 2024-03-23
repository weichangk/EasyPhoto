/*
 * @Author: weick
 * @Date: 2023-12-10 23:06:34
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 22:08:21
 */

#pragma once
#include "models.h"
#include <QAbstractListModel>

class CompressionListViewModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit CompressionListViewModel(QObject *parent = 0);
    void changeModels(const QList<imagecompression::Data> &datas);
    void changeData(int row, const imagecompression::Data &data);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

protected:
    QList<imagecompression::Data> m_Datas;
};
