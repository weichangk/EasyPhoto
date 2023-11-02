#pragma once
#include <QAbstractItemModel>
#include <QPixmap>
#include "imagefunc.h"

class ImageFuncModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ImageFuncModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    void append(ImageFunc func);
    void clear();

private:
    QList<ImageFunc> m_Funcs;
};
