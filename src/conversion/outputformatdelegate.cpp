#include "conversion/outputformatdelegate.h"
#include "conversion/model.h"
#include "core/painter.h"

#include <QMouseEvent>
#include <QPainter>
#include <QFontMetricsF>

using namespace qtmaterialcore;

OutputFormatDelegate::OutputFormatDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void OutputFormatDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<SOuputFormat>();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRect rc = option.rect;
    bool pressed = m_nEventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto bgRect = rc.adjusted(0, 0, -8, -8);
    int radius = 4;

    QColor bgColor = Qt::transparent;
    if (hover) {
        bgColor = QColor("#352c52");
    }
    if (selected) {
        bgColor = QColor("#473e6a");
    }
    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

    auto desRect = QRect(bgRect.x() + 8, bgRect.y(), bgRect.width() - 8 - 8, bgRect.height());
    QColor desColor = QColor("#ffffff");
    QPen pen(desColor);
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPixelSize(13);
    painter->setFont(font);
    QString des = data.des;
    QFontMetricsF metrics(font);
    if (metrics.horizontalAdvance(des) > desRect.width()) {
        des = metrics.elidedText(des, Qt::ElideMiddle, desRect.width());
    }
    painter->drawText(desRect, Qt::AlignCenter, des);
    painter->setPen(Qt::NoPen);
}

bool OutputFormatDelegate::eventFilter(QObject *object, QEvent *event) {
    int type = event->type();
    if (type == QEvent::MouseMove || type == QEvent::MouseButtonPress || type == QEvent::MouseButtonRelease) {
        m_nEventType = type;
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

QSize OutputFormatDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return m_Size;
}