#include "enhancement/modellistdelegate.h"
#include "enhancement/model.h"
#include "core/painter.h"

#include <QMouseEvent>
#include <QPainter>
#include <QFontMetricsF>

using namespace qtmaterialcore;

EnhanceModelListDelegate::EnhanceModelListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void EnhanceModelListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<SEnhanceModelData>();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRect rc = option.rect;
    bool pressed = m_EventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto bgRect = rc.adjusted(0, 0, 0, 0);
    int radius = 8;

    QColor bgColor = QColor("#241f37");
    if (hover) {
        bgColor = QColor("#2d2741");
    }
    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

    auto pixmapRect = rc.adjusted(4, 4, -4, -28);
    Painter::paintPixmap(painter, pixmapRect, data.thumbnail, 1, radius, true);

    if (hover) {
        QColor borderColor = QColor("#703eff");
        QPen pen(borderColor);
        painter->setPen(pen);
        painter->drawRoundedRect(bgRect.adjusted(1, 1, -1, -1), radius, radius);
        painter->setPen(Qt::NoPen);
    }

    auto nameRect = QRect(pixmapRect.left(), pixmapRect.bottom(), pixmapRect.width(), 28);
    QColor nameColor = QColor("#ffffff");
    QPen pen(nameColor);
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPixelSize(13);
    painter->setFont(font);
    QString fileName = data.name;
    QFontMetricsF metrics(font);
    if (metrics.horizontalAdvance(fileName) > nameRect.width()) {
        fileName = metrics.elidedText(fileName, Qt::ElideMiddle, nameRect.width());
    }
    painter->drawText(nameRect, Qt::AlignCenter, fileName);
    painter->setPen(Qt::NoPen);
}

bool EnhanceModelListDelegate::eventFilter(QObject *object, QEvent *event) {
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

QSize EnhanceModelListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return m_Size;
}