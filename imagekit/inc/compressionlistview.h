/*
 * @Author: weick
 * @Date: 2023-12-13 00:09:55
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-13 23:36:11
 */

#pragma once
#include "compressionlistviewmodel.h"
#include <QListView>

class CompressionListView : public QListView {
    Q_OBJECT
public:
    explicit CompressionListView(QWidget *parent = 0);
    void chageData(const QList<Models::CompressionData> &datas);
    Models::CompressionData data(int i) const;
    int count() const;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;

private:
    CompressionListViewModel *m_Model = 0;
};
