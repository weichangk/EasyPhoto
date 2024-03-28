/*
 * @Author: weick 
 * @Date: 2024-03-28 07:49:56 
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-28 08:16:11
 */

#pragma once
#include "agui_global.h"
#include <QAbstractListModel>

template <typename T>
class AGUI_EXPORT AListViewModel : public QAbstractListModel {
    // Q_OBJECT
public:
    explicit AListViewModel(QObject *parent = 0);
    void changeModels(const QList<T> &datas);
    void changeData(int row, const T &data);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

protected:
    QList<T> datas_;
};