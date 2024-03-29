/*
 * @Author: weick 
 * @Date: 2024-03-28 07:57:39 
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-28 08:16:32
 */

#include "inc/alistview.h"
#include "inc/alistviewmodel.h"
#include <QMouseEvent>

template <typename T>
AListView<T>::AListView(QWidget *parent) :
    QListView(parent) {
    setAttribute(Qt::WA_StyledBackground);
    setMouseTracking(true);
    setStyleSheet("border:0px; background-color:transparent;");
    setSpacing(0);
    view_model_ = new AListViewModel<T>(this);
    setModel(view_model_);
}

template <typename T>
void AListView<T>::chageData(const QList<T> &datas) {
    view_model_->changeModels(datas);
}

template <typename T>
T AListView<T>::data(int i) const {
    return view_model_->data(view_model_->index(i, 0), Qt::UserRole).value<T>();
}

template <typename T>
int AListView<T>::count() const {
    return view_model_->rowCount(QModelIndex());
}

template <typename T>
void AListView<T>::mouseMoveEvent(QMouseEvent *event) {
    if (indexAt(event->pos()).row() != -1) {
        setCursor(Qt::PointingHandCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

template <typename T>
void AListView<T>::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
}