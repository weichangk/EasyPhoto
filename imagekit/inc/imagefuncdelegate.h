#pragma once
#include <QItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>

class ImageFuncDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ImageFuncDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setSize(QSize size);

private:
    QSize m_Size = QSize(0, 0);
};
