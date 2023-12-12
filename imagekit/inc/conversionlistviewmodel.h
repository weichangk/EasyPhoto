/*
 * @Author: weick
 * @Date: 2023-12-10 23:06:34
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-13 00:00:16
 */

#pragma once
#include "conversionmodels.h"
#include <QAbstractListModel>

using ConversionDatas = QList<ConversionData>;

class ConversionListViewModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit ConversionListViewModel(QObject *parent = 0);
    void changeModels(const ConversionDatas &datas);
    void changeData(int row, const ConversionData &data);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

protected:
    ConversionDatas m_Datas;
};
