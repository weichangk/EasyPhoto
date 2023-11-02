#include "inc/imagefuncdelegate.h"

ImageFuncDelegate::ImageFuncDelegate(QObject *parent) : QItemDelegate(parent)
{
}

void ImageFuncDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_ASSERT(index.isValid());
}

QSize ImageFuncDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return m_Size;
}

void ImageFuncDelegate::setSize(QSize size)
{
    m_Size = size;
}
