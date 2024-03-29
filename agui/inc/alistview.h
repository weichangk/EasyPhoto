/*
 * @Author: weick
 * @Date: 2024-03-28 07:57:04
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-28 08:16:07
 */

#pragma once
#include "alistviewmodel.h"
#include <QListView>
#include <QMouseEvent>

template <typename T>
class AListView : public QListView {
public:
    AListView(QWidget *parent) :
        QListView(parent) {
        setAttribute(Qt::WA_StyledBackground);
        setMouseTracking(true);
        setStyleSheet("border:0px; background-color:transparent;");
        setSpacing(0);
        view_model_ = new AListViewModel<T>(this);
        setModel(view_model_);
    }

    void chageData(const QList<T> &datas) {
        view_model_->changeModels(datas);
    }

    T data(int i) const {
        return view_model_->data(view_model_->index(i, 0), Qt::UserRole).value<T>();
    }

    int count() const {
        return view_model_->rowCount(QModelIndex());
    }

protected:
    void mouseMoveEvent(QMouseEvent *event) {
        if (indexAt(event->pos()).row() != -1) {
            setCursor(Qt::PointingHandCursor);
        } else {
            setCursor(Qt::ArrowCursor);
        }
    }

    void currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    }

private:
    AListViewModel<T> *view_model_ = 0;
};
