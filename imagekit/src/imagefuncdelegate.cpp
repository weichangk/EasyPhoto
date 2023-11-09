#include "inc/imagefuncdelegate.h"
#include "inc/imagefunc.h"

ImageFuncDelegate::ImageFuncDelegate(QObject *parent) : QItemDelegate(parent)
{

}

void ImageFuncDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_ASSERT(index.isValid());
    if(index.data().canConvert<ImageFunc>())
    {
        ImageFunc imageFunc=qvariant_cast<ImageFunc>(index.data());
        auto sd = option.rect;
        painter->setRenderHint(QPainter::Antialiasing);

        QFont font;
        font.setHintingPreference(QFont::PreferFullHinting);
    }
}

bool ImageFuncDelegate::eventFilter(QObject *object, QEvent *event)
{
    return QItemDelegate::eventFilter(object, event);
}

QSize ImageFuncDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return m_Size;
}
