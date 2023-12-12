/*
 * @Author: weick
 * @Date: 2023-12-12 23:58:34
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-13 00:08:44
 */

#include "inc/conversionlistdelegate.h"
#include <QMouseEvent>

ConversionListDelegate::ConversionListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void ConversionListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
}

bool ConversionListDelegate::eventFilter(QObject *object, QEvent *event) {
    int type = event->type();
    if (type == QEvent::MouseButtonPress || type == QEvent::MouseButtonRelease) {
        m_EventType = type;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent) {
            QPoint pos = mouseEvent->pos();
            m_CurPos = pos;
            QWidget *curWidget = static_cast<QWidget *>(object);
            curWidget->update();
        }
    }
    return QStyledItemDelegate::eventFilter(object, event);
}

QSize ConversionListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return m_Size;
}

void ConversionListDelegate::changeSizeHint(const QSize &size) {
    m_Size = size;
}
