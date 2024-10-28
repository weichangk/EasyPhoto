/*
 * @Author: weick
 * @Date: 2023-12-13 00:09:55
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 21:08:30
 */

#pragma once
#include "models.h"
#include "conversionlistviewmodel.h"
#include <QListView>

namespace imageconversion {
class ConversionListView : public QListView {
    Q_OBJECT
public:
    explicit ConversionListView(QWidget *parent = 0);
    void chageData(const QList<Data> &datas);
    Data data(int i) const;
    int count() const;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;

private:
    ConversionListViewModel *m_Model = 0;
};
} // namespace imageconversion