#include "comp/listdelegate.h"
#include "comp/definerect.h"
#include "core/painter.h"
#include "core/object.h"
#include "core/theme.h"
#include "widget/listview.h"
#include "types.h"

#include <QMouseEvent>
#include <QPainter>
#include <QFontMetricsF>
#include <QComboBox>
#include <QApplication>
#include <QTimer>
#include <QListView>

using namespace QtmCore;

CompListDelegate::CompListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void CompListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<SImageData>();
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
    QColor bgColor = Qt::transparent;

    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

    auto checkedRect = compListCheckedRect(bgRect);
    if (data.is_checked) {
        QColor checkBgColor = QColor(QtmCore::Theme::colors().value("color4"));
        if (checkedRect.contains(m_CurPos)) {
            if (hover) {
                checkBgColor.setAlphaF(0.9);
            }
            if (pressed) {
                checkBgColor.setAlphaF(0.8);
            }
        }
        painter->setBrush(checkBgColor);
        painter->drawRoundedRect(checkedRect, 2, 2);
        painter->setBrush(Qt::NoBrush);
        Painter::paintPixmap(painter, checkedRect, data.checked_icon, 1, 0, true);
    } else {
        QColor checkBgColor = QColor(QtmCore::Theme::bgColors().value("color2"));
        if (checkedRect.contains(m_CurPos)) {
            if (hover) {
                checkBgColor.setAlphaF(0.9);
            }
            if (pressed) {
                checkBgColor.setAlphaF(0.8);
            }
        }
        painter->setBrush(checkBgColor);
        painter->drawRoundedRect(checkedRect, 2, 2);
        painter->setBrush(Qt::NoBrush);
        QColor checkBorderColor = QColor(QtmCore::Theme::bdColors().value("color3"));
        if (checkedRect.contains(m_CurPos)) {
            if (hover) {
                checkBorderColor.setAlphaF(0.9);
            }
            if (pressed) {
                checkBorderColor.setAlphaF(0.8);
            }
        }
        QPen pen(checkBorderColor);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->drawRoundedRect(checkedRect, 2, 2);
        painter->setPen(Qt::NoPen);
    }

    auto delRect = compListDelRect(bgRect);
    QColor delBgColor = QColor(QtmCore::Theme::colors().value("color5"));
    if (delRect.contains(m_CurPos)) {
        if (hover) {
            delBgColor.setAlphaF(0.9);
        }
        if (pressed) {
            delBgColor.setAlphaF(0.8);
        }
    }
    if (hover || pressed) {
        painter->setBrush(delBgColor);
        painter->drawRoundedRect(delRect, 8, 8);
        painter->setBrush(Qt::NoBrush);
        Painter::paintPixmap(painter, delRect, data.delete_icon, 1, 0, true);
    }

    auto nameRect = compListNameRect(bgRect);
    QColor nameColor = QColor(QtmCore::Theme::foreColors().value("color0"));
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

    auto resolutionRect = compListResolutionRect(bgRect);
    painter->drawText(resolutionRect, Qt::AlignLeft | Qt::AlignVCenter, QString("%1x%2").arg(data.resolution.width()).arg(data.resolution.height()));

    auto sizeRect = compListSizeRect(bgRect);
    if(data.state == EImageState_Success) {
        painter->drawText(sizeRect, Qt::AlignCenter, QString("%1 --> %2").arg(data.intput_size).arg(data.output_size));
    }
    else {
        painter->drawText(sizeRect, Qt::AlignCenter, data.intput_size);
    }
    painter->setPen(Qt::NoPen);

    auto stateRect = compListStateRect(bgRect);
    Painter::paintPixmap(painter, stateRect, data.state_icons[data.state], 1, 0, true);

    auto compRect = compListConvRect(bgRect);
    int compRadius = 12;
    QColor compBgColor = Qt::transparent;
    painter->setBrush(compBgColor);
    painter->drawRoundedRect(compRect, compRadius, compRadius);
    painter->setBrush(Qt::NoBrush);

    QColor compBorderColor = QColor(QtmCore::Theme::colors().value("color3"));
    QPen compBorderPen(compBorderColor);
    painter->setPen(compBorderPen);
    painter->drawRoundedRect(compRect.adjusted(1, 1, -1, -1), compRadius, compRadius);
    painter->setPen(Qt::NoPen);

    auto compTextRect = compRect;
    QColor compTextColor = QColor(QtmCore::Theme::foreColors().value("color0"));
    QPen compTextPen(compTextColor);
    painter->setPen(compTextPen);
    QFont compTextFont = painter->font();
    compTextFont.setPixelSize(12);
    painter->setFont(compTextFont);
    QString compText = tr("Compress");
    painter->drawText(compTextRect, Qt::AlignCenter, compText);
    painter->setPen(Qt::NoPen);
}

bool CompListDelegate::eventFilter(QObject *object, QEvent *event) {
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

QSize CompListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (m_bIsListMode) {
        QWidget *parent = static_cast<QWidget *>(this->parent());
        return QSize(parent->width(), n_ListItemHeight);
    }
    return m_Size;
}

void CompListDelegate::setListMode(bool b) {
    m_bIsListMode = b;
}

bool CompListDelegate::isListMode() const {
    return m_bIsListMode;
}