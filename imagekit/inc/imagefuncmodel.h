#pragma once
#include <QAbstractItemModel>
#include <QPixmap>
#include "imagefunc.h"

class ImageFuncModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ImageFuncModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    void append(ImageFunc *func);
    void append(QList<ImageFunc *> funcs);
    void clear();

private:
    QList<ImageFunc *> m_Funcs;
};
