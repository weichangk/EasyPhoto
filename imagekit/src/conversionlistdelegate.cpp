/*
 * @Author: weick
 * @Date: 2023-12-12 23:58:34
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-09 00:22:51
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
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);

    QRect rc = option.rect;
    bool pressed = m_EventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto borderRect = rc.adjusted(1 + 12, 1 + 12, -1, -1);
    painter->setBrush(QColor("#303338"));
    painter->drawRoundedRect(borderRect, 10, 10);
    painter->setBrush(Qt::NoBrush);

    auto pixmapRect = QRect(rc.x() + 12, rc.y() + 12, 148, 148);
    if (data.m_IsAdd) {
        APainterHelper::paintPixmap(painter, pixmapRect, data.m_Thumbnail, 1, 10, true);
    } else {
        pixmapRect = pixmapRect.adjusted(4, 4, -4, -4);
        APainterHelper::paintPixmap(painter, pixmapRect, data.m_Thumbnail, 1, 10, true);
    }

    if(hover)
    {
        auto delIconRect = QRect(borderRect.x() + borderRect.width() - data.m_DelIcon.width() - 6, borderRect.y() + 6, data.m_DelIcon.width(), data.m_DelIcon.height());
        APainterHelper::paintPixmap(painter, delIconRect, data.m_DelIcon, 1, 10, true);
    }

    QPen pen(QColor("#1F1F1F"));
    pen.setWidth(1);
    painter->setPen(pen);
    if (hover || pressed) {
        painter->drawRoundedRect(borderRect, 10, 10);
    }
    painter->setPen(Qt::NoPen);

    pen.setColor(QColor("#575859"));
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPointSizeF(11);
    painter->setFont(font);
    auto nameRect = QRect(rc.x() + 12 + 8, rc.y() + 12 + 148 - 24, rc.width() - 12 - 8 - 8, 24);
    painter->drawText(nameRect, data.m_FileName);
    painter->setPen(Qt::NoPen);

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
