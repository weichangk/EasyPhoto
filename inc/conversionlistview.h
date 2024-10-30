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