#pragma once
#include <QAbstractItemModel>
#include <QPixmap>
#include "imagefunc.h"

class ImageFuncModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ImageFuncModel(QObject *parent = 0);
    void changeData(const QList<ImageFunc> &datas);
    void changeData(int row, const ImageFunc &data);
    void addData(QList<ImageFunc> &datas);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    QList<ImageFunc> m_Datas;
};
