/*
 * @Author: weick
 * @Date: 2023-12-12 23:58:34
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-13 23:52:43
 */

#include "inc/conversionlistdelegate.h"
#include "inc/conversionmodels.h"
#include <QMouseEvent>
#include <QPainter>

ConversionListDelegate::ConversionListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void ConversionListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<ConversionData>();
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    QRect rc = option.rect;

    bool pressed = m_EventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    painter->setPen(Qt::NoPen);
    if (data.m_IsAdd) {
        painter->drawPixmap(17, 17, data.m_Thumbnail.width(), data.m_Thumbnail.height(), data.m_Thumbnail); // 96 *96
    } else {
        auto thumb = data.m_Thumbnail.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap(3, 3, 100, 100, thumb);
    }

    QPen pen(QColor("#E5E5E5"));
    pen.setWidth(1);
    painter->setPen(pen);
    auto borderRect = rc.adjusted(1, 1, -1, -1);
    if (hover || pressed) {
        painter->drawRoundedRect(borderRect, 10, 10);
    }
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
