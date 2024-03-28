/*
 * @Author: weick 
 * @Date: 2024-03-28 07:57:04 
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-28 08:16:07
 */

#pragma once
#include "agui_global.h"
#include "alistviewmodel.h"
#include <QListView>

template <typename T>
class AGUI_EXPORT AListView : public QListView {
    // Q_OBJECT
public:
    explicit AListView(QWidget *parent = 0);
    void chageData(const QList<T> &datas);
    T data(int i) const;
    int count() const;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;

private:
    AListViewModel<T> *view_model_ = 0; 
};