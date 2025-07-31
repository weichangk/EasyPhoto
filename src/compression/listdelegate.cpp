#include "compression/listdelegate.h"
#include "compression/model.h"
#include "compression/definerect.h"
#include "core/painter.h"
#include "core/object.h"
#include "widget/listview.h"

#include <QMouseEvent>
#include <QPainter>
#include <QFontMetricsF>
#include <QComboBox>
#include <QApplication>
#include <QTimer>
#include <QListView>

using namespace qtmaterialcore;

CompressionListDelegate::CompressionListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void CompressionListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<SCompressionData>();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRect rc = option.rect;
    bool pressed = m_EventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;
    bool checked = data.is_checked;

    auto bgRect = rc.adjusted(0, 0, 0, 0);
    int radius = 0;
    // QColor bgColor = QColor("#2a2a3c");
    // if (hover) {
    //     bgColor = QColor("#2d2741");
    // }
    QColor bgColor = QColor("#1a1627");
    // if (hover) {
    //     bgColor = QColor("#2d2741");
    // }
    // if(checked) {
    //     bgColor = QColor("#202031");
    // }

    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

    // if (!m_bIsListMode) {
    //     auto pixmapRect = rc.adjusted(4, 24 + 8, -12, -12);
    //     Painter::paintPixmap(painter, pixmapRect, data.thumbnail, 1, radius, true);
    // }

    // QColor borderColor = QColor("#2a2a3c");
    // if (hover) {
    //     borderColor = QColor("#703eff");
    // }
    // QPen borderPen(borderColor);
    // painter->setPen(borderPen);
    // painter->drawRoundedRect(bgRect.adjusted(1, 1, -1, -1), radius, radius);
    // painter->setPen(Qt::NoPen);

    auto checkedRect = convListCheckedRect(bgRect);
    if (data.is_checked) {
        QColor checkBgColor = QColor("#a070ff");
        if (checkedRect.contains(m_CurPos)) {
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
        if (checkedRect.contains(m_CurPos)) {
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

    auto delRect = convListDelRect(bgRect);
    QColor delBgColor = QColor("#fa7681");
    if (delRect.contains(m_CurPos)) {
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

    auto nameRect = convListNameRect(bgRect);
    QColor nameColor = QColor("#ffffff");
    QPen penName(nameColor);
    painter->setPen(penName);
    QFont fontName = painter->font();
    fontName.setPixelSize(12);
    painter->setFont(fontName);
    QString fileName = data.file_name;
    QFontMetricsF fileMetrics(fontName);
    if (fileMetrics.horizontalAdvance(fileName) > nameRect.width()) {
        fileName = fileMetrics.elidedText(fileName, Qt::ElideMiddle, nameRect.width());
    }
    painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter, fileName);

    auto resolutionRect = convListResolutionRect(bgRect);
    painter->drawText(resolutionRect, Qt::AlignLeft | Qt::AlignVCenter, QString("%1x%2").arg(data.resolution.width()).arg(data.resolution.height()));

    painter->setPen(Qt::NoPen);

    auto stateRect = convListStateRect(bgRect);
    Painter::paintPixmap(painter, stateRect, data.state_icons[data.state], 1, 0, true);

    auto convRect = convListConvRect(bgRect);
    int convRadius = 10;
    QColor convBgColor = QColor("#2c2c3f");
    if(hover) {
        convBgColor = QColor("#433767");
    }
    if(pressed) {
        convBgColor = QColor("#2f2b47");
    }
    painter->setBrush(convBgColor);
    painter->drawRoundedRect(convRect, convRadius, convRadius);
    painter->setBrush(Qt::NoBrush);

    QColor convBorderColor = QColor("#a070ff");
    QPen convBorderPen(convBorderColor);
    painter->setPen(convBorderPen);
    painter->drawRoundedRect(convRect.adjusted(1, 1, -1, -1), convRadius, convRadius);
    painter->setPen(Qt::NoPen);

    auto convTextRect = convRect;
    QColor convTextColor = QColor("#ffffff");
    QPen convTextPen(convTextColor);
    painter->setPen(convTextPen);
    QFont convTextFont = painter->font();
    convTextFont.setPixelSize(12);
    painter->setFont(convTextFont);
    QString convText = tr("Convert");
    painter->drawText(convTextRect, Qt::AlignCenter, convText);
    painter->setPen(Qt::NoPen);
}

bool CompressionListDelegate::eventFilter(QObject *object, QEvent *event) {
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

QSize CompressionListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (m_bIsListMode) {
        QWidget *parent = static_cast<QWidget *>(this->parent());
        return QSize(parent->width(), n_ListItemHeight);
    }
    return m_Size;
}

void CompressionListDelegate::setListMode(bool b) {
    m_bIsListMode = b;
}

bool CompressionListDelegate::isListMode() const {
    return m_bIsListMode;
}