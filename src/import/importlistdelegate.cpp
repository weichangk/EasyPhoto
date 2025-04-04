#include "import/importlistdelegate.h"
#include "import/importmodel.h"
#include "core/painter.h"

#include <QMouseEvent>
#include <QPainter>
#include <QFontMetricsF>

using namespace qtmaterialcore;

ImportListDelegate::ImportListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void ImportListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<SImportListItem>();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRect rc = option.rect;
    bool pressed = m_EventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto bgRect = rc.adjusted(0, 0, 0, 0);
    int radius = 4;

    QColor bgColor = QColor("#241f37");
    if (hover) {
        bgColor = QColor("#2d2741");
    }
    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

    auto pixmapRect = rc.adjusted(0, 0, 0, 0);
    Painter::paintPixmap(painter, pixmapRect, data.thumbnail, 1, radius, true);

    if (hover) {
        QColor borderColor = QColor("#703eff");
        QPen pen(borderColor);
        painter->setPen(pen);
        painter->drawRoundedRect(bgRect.adjusted(1, 1, -1, -1), radius, radius);
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

bool ImportListDelegate::eventFilter(QObject *object, QEvent *event) {
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

QSize ImportListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return m_Size;
}