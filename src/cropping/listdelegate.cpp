#include "cropping/listdelegate.h"
#include "cropping/model.h"
#include "core/painter.h"

#include <QMouseEvent>
#include <QPainter>
#include <QFontMetricsF>

using namespace qtmaterialcore;

CroppingListDelegate::CroppingListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void CroppingListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<SCroppingData>();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRect rc = option.rect;
    bool pressed = m_EventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto bgRect = rc.adjusted(0, 0, -8, -8);
    int radius = 4;

    QColor bgColor = QColor("#241f37");
    if (hover) {
        bgColor = QColor("#2d2741");
    }
    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

        auto pixmapRect = rc.adjusted(4, 24, -12, -12);
        Painter::paintPixmap(painter, pixmapRect, data.thumbnail, 1, radius, true);

    if (hover) {
        QColor borderColor = QColor("#703eff");
        QPen pen(borderColor);
        painter->setPen(pen);
        painter->drawRoundedRect(bgRect.adjusted(1, 1, -1, -1), radius, radius);
        painter->setPen(Qt::NoPen);
    }

    auto checkedRect = QRect(bgRect.x() + 4, bgRect.y() + 4, 16, 16);
    if (data.is_checked) {
        QColor checkBgColor = QColor("#a070ff");
        if(checkedRect.contains(m_CurPos)) {
            if (hover) {
                checkBgColor = QColor("#ad84ff");
            }
            if (pressed) {
                checkBgColor = QColor("#bb99ff");
            }
        }
        painter->setBrush(checkBgColor);
        painter->drawRoundedRect(checkedRect, 2, 2);
        painter->setBrush(Qt::NoBrush);
        Painter::paintPixmap(painter, checkedRect, data.checked_icon, 1, 0, true);
    } else {
        QColor checkBgColor = QColor("#2f2f36");
        if(checkedRect.contains(m_CurPos)) {
            if (hover) {
                checkBgColor = QColor("#3a3a43");
            }
            if (pressed) {
                checkBgColor = QColor("#464650");
            }
        }
        painter->setBrush(checkBgColor);
        painter->drawRoundedRect(checkedRect, 2, 2);
        painter->setBrush(Qt::NoBrush);
        QColor checkBorderColor = QColor("#575766");
        QPen pen(checkBorderColor);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->drawRoundedRect(checkedRect, 2, 2);
        painter->setPen(Qt::NoPen);
    }

    auto delRect = QRect(bgRect.right() - 4 - 16, bgRect.y() + 4, 16, 16);
    QColor delBgColor = QColor("#fa7681");
    if(delRect.contains(m_CurPos)) {
        if (hover) {
            delBgColor.setAlpha(200);
        }
        if (pressed) {
            delBgColor.setAlpha(100);
        }
    }
    if (hover || pressed) {
        painter->setBrush(delBgColor);
        painter->drawRoundedRect(delRect, 8, 8);
        painter->setBrush(Qt::NoBrush);
        Painter::paintPixmap(painter, delRect, data.delete_icon, 1, 0, true);
    }
}

bool CroppingListDelegate::eventFilter(QObject *object, QEvent *event) {
    int type = event->type();
    if (type == QEvent::MouseMove || type == QEvent::MouseButtonPress || type == QEvent::MouseButtonRelease) {
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

QSize CroppingListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return m_Size;
}