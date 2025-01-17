#include "conversion/listdelegate.h"
#include "conversion/model.h"
#include "core/painter.h"

#include <QMouseEvent>
#include <QPainter>
#include <QFontMetricsF>

using namespace qtmaterialcore;

ListDelegate::ListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void ListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<Data>();
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);

    QRect rc = option.rect;
    bool pressed = m_EventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto pixmapRect = rc.adjusted(0, 24, -8, -8);
    Painter::paintPixmap(painter, pixmapRect, data.thumbnail, 1, 8, true);

    auto borderRect = rc.adjusted(0, 0, -8, -8);
    painter->setBrush(QColor("#2F2D2D"));
    painter->drawRoundedRect(borderRect, 8, 8);
    painter->setBrush(Qt::NoBrush);

    auto checkedconRect = QRect(borderRect.x() + 4, borderRect.y() + 4, data.checked_icon.width(), data.checked_icon.height());
    Painter::paintPixmap(painter, checkedconRect, data.is_checked ? data.checked_icon : data.unchecked_icon, 1, 0, true);

    if (hover) {
        auto delIconRect = QRect(borderRect.x() + borderRect.width() - data.delete_icon.width() - 4, borderRect.y() + 4, data.delete_icon.width(), data.delete_icon.height());
        Painter::paintPixmap(painter, delIconRect, data.delete_icon, 1, 0, true);
    }

    QPen pen(QColor("#1F1F1F"));
    pen.setWidth(1);
    painter->setPen(pen);
    if (hover || pressed) {
        painter->drawRoundedRect(borderRect, 8, 8);
    }
    painter->setPen(Qt::NoPen);

    pen.setColor(QColor("#575859"));
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPointSizeF(11);
    painter->setFont(font);
    QString fileName = data.file_name;
    auto nameRect = QRect(borderRect.x() + 20, borderRect.y(), borderRect.width() - 40, 24);
    QFontMetricsF metrics(font);
    if (metrics.horizontalAdvance(fileName) > nameRect.width()) {
        fileName = metrics.elidedText(fileName, Qt::ElideMiddle, nameRect.width(), Qt::TextShowMnemonic);
    }
    painter->drawText(nameRect, Qt::PlainText, fileName);
    painter->setPen(Qt::NoPen);
}

bool ListDelegate::eventFilter(QObject *object, QEvent *event) {
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

QSize ListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return m_Size;
}

void ListDelegate::changeSizeHint(const QSize &size) {
    m_Size = size;
}