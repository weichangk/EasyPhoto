/*
 * @Author: weick
 * @Date: 2023-12-13 00:09:55
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-13 23:36:11
 */

#pragma once
#include "conversionmodels.h"
#include "conversionlistviewmodel.h"
#include <QListView>


using ConversionDatas = QList<ConversionData>;
class ConversionListView : public QListView {
    Q_OBJECT
public:
    explicit ConversionListView(QWidget *parent = 0);
    void chageData(const ConversionDatas &datas);
    ConversionData data(int i) const;
    int count() const;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;

private:
    ConversionListViewModel *m_Model = 0;
};
