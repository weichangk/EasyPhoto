/*
 * @Author: weick
 * @Date: 2023-12-05 23:01:44
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:01:44
 */

#pragma once
#include <QListView>
#include <QMoveEvent>
#include "imagefunc.h"
#include "imagefuncmodel.h"

class ImageFuncView : public QListView {
    Q_OBJECT
public:
    ImageFuncView(QWidget *parent = 0);
    void changeModel(const QList<ImageFunc> &datas);
    void changeModel(int row, const ImageFunc &data);
    void addModel(QList<ImageFunc> &datas);
    ImageFunc model(int row) const;
    int rowCount() const;

protected:
    void mouseMoveEvent(QMouseEvent *e) override;
    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;

private:
    ImageFuncModel *m_Model = nullptr;
};
