/*
 * @Author: weick
 * @Date: 2023-12-12 23:58:34
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-19 23:59:39
 */

#include "inc/conversionlistdelegate.h"
#include "inc/conversionmodels.h"
#include "../acore/inc/apainterhelper.h"
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
    auto pixmapRect = QRect(rc.x() + 12, rc.y() + 12, 148, 148);
    if (data.m_IsAdd) {
        APainterHelper::paintPixmap(painter, pixmapRect, data.m_Thumbnail, 1, 10, false);
    } else {
        auto thumb = data.m_Thumbnail.scaled(148, 148, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        APainterHelper::paintPixmap(painter, pixmapRect, thumb, 1, 10, false);
    }

    QPen pen(QColor("#1F1F1F"));
    pen.setWidth(1);
    painter->setPen(pen);
    auto borderRect = rc.adjusted(1 + 12, 1 + 12, -1, -1);
    if (hover || pressed) {
        painter->drawRoundedRect(borderRect, 10, 10);
    }

    pen.setColor(QColor("#575859"));
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPointSizeF(11);
    painter->setFont(font);
    auto nameRect = QRect(rc.x() + 12 + 8, rc.y() + 12 + 148 - 24, rc.width() - 12 - 8 - 8, 24);
    painter->drawText(nameRect, data.m_FileName);

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
