/*
 * @Author: weick
 * @Date: 2023-12-12 23:58:34
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-15 23:17:23
 */

#include "inc/conversionlistdelegate.h"
#include "inc/conversionmodels.h"
#include "../acore/inc/apainterhelper.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFontMetricsF>

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

    auto borderRect = rc.adjusted(1 + 8, 1 + 8, -1, -1);
    painter->setBrush(QColor("#303338"));
    painter->drawRoundedRect(borderRect, 10, 10);
    painter->setBrush(Qt::NoBrush);

    auto pixmapRect = QRect(rc.x() + 8, rc.y() + 8, 176, 176);
    pixmapRect = pixmapRect.adjusted(20, 30, -20, -30);
    APainterHelper::paintPixmap(painter, pixmapRect, data.m_Thumbnail, 1, 10, true);

    auto checkedconRect = QRect(borderRect.x() + 4, borderRect.y() + 4, data.m_CheckedIcon.width(), data.m_CheckedIcon.height());
    APainterHelper::paintPixmap(painter, checkedconRect, data.m_IsChecked ? data.m_CheckedIcon : data.m_UnCheckedIcon, 1, 0, true);

    if (hover) {
        auto delIconRect = QRect(borderRect.x() + borderRect.width() - data.m_DelIcon.width() - 4, borderRect.y() + 4, data.m_DelIcon.width(), data.m_DelIcon.height());
        APainterHelper::paintPixmap(painter, delIconRect, data.m_DelIcon, 1, 0, true);
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
    QString fileName = data.m_FileName;
    auto nameRect = QRect(borderRect.x() + 20, borderRect.y() + borderRect.height() - 24, borderRect.width() - 40, 24);
    QFontMetricsF metrics(font);
    if (metrics.horizontalAdvance(fileName) > nameRect.width()) {
        fileName = metrics.elidedText(fileName, Qt::ElideMiddle, nameRect.width(), Qt::TextShowMnemonic);
    }
    painter->drawText(nameRect, Qt::PlainText, fileName);
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
