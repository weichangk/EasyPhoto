#include "home/funcitemdelegate.h"
#include "home/model.h"
#include "core/painter.h"

#include <QMouseEvent>
#include <QPainter>
#include <QFontMetricsF>

using namespace qtmaterialcore;

FuncItemDelegate::FuncItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void FuncItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<SFuncItemData>();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRect rc = option.rect;
    bool pressed = m_nEventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto bgRect = rc.adjusted(0, 0, 0, 0);
    int radius = 12;

    QColor bgColor = QColor("#2d2741");
    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

    auto thumbnailRect = QRect(bgRect.x() + 4, bgRect.y() + 4, 226, 128);
    Painter::paintPixmap(painter, thumbnailRect, data.thumbnail, 1, radius - 2, true);

    auto btnRect = QRect(bgRect.x() + 18, thumbnailRect.bottom() + 20, bgRect.width() - 36, 36);
    QColor btnColor = QColor("#703eff");
    if(btnRect.contains(m_CurPos)) {
        if (hover) {
            btnColor = QColor("#8054ff");
        }
        if (pressed) {
            btnColor = QColor("#6230f3");
        }
    }
    if (hover) {
        painter->setBrush(btnColor);
        painter->drawRoundedRect(btnRect, 10, 10);
        painter->setBrush(Qt::NoBrush);
        if (data.btn_type == EFuncItemBtnType::AddFile) {
            QColor addFileColor = QColor("#ffffff");
            QPen addFilePen(addFileColor);
            painter->setPen(addFilePen);
            QFont addFileFont = painter->font();
            addFileFont.setPixelSize(12);
            addFileFont.setBold(true);
            auto addFileFontMetrics = QFontMetrics(addFileFont);
            int w = addFileFontMetrics.horizontalAdvance(data.addfile_text);
            int h = addFileFontMetrics.height();
            auto addFileRect = QRect(btnRect.left() + (btnRect.width() - w - 24) / 2 + 24, btnRect.top() + (btnRect.height() - h) / 2, w, h);
            painter->setFont(addFileFont);
            painter->drawText(addFileRect, Qt::AlignCenter, data.addfile_text);
            painter->setPen(Qt::NoPen);
            auto addFileIconRect = QRect(addFileRect.x() - 24, btnRect.top() + (btnRect.height() - 24) / 2, 24, 24);
            Painter::paintPixmap(painter, addFileIconRect, data.addfile_icon, 1, 0, true);
        } else if (data.btn_type == EFuncItemBtnType::StartNow) {
            QColor startNowColor = QColor("#ffffff");
            QPen startNowPen(startNowColor);
            painter->setPen(startNowPen);
            QFont startNowFont = painter->font();
            startNowFont.setPixelSize(12);
            startNowFont.setBold(true);
            auto startNowFontMetrics = QFontMetrics(startNowFont);
            int w = startNowFontMetrics.horizontalAdvance(data.startnew_text);
            int h = startNowFontMetrics.height();
            auto startNowRect = QRect(btnRect.left() + (btnRect.width() - w - 24) / 2, btnRect.top() + (btnRect.height() - h) / 2, w, h);
            painter->setFont(startNowFont);
            painter->drawText(startNowRect, Qt::AlignCenter, data.startnew_text);
            painter->setPen(Qt::NoPen);
            auto startNowIconRect = QRect(startNowRect.right(), btnRect.top() + (btnRect.height() - 24) / 2, 24, 24);
            auto startnew_icon = data.startnew_icon.copy(0, 0, data.startnew_icon.width() / 4, data.startnew_icon.height());
            Painter::paintPixmap(painter, startNowIconRect, startnew_icon, 1, 0, true);
        }
    } else {
        auto titleRect = QRect(bgRect.x() + 18, thumbnailRect.bottom() + 16, bgRect.width() - 36, 24);
        QColor titleColor = QColor("#ffffff");
        QPen titlePen(titleColor);
        painter->setPen(titlePen);
        QFont titleFont = painter->font();
        titleFont.setPixelSize(12);
        titleFont.setBold(true);
        painter->setFont(titleFont);
        QString title = data.title;
        QFontMetricsF titleMetrics(titleFont);
        if (titleMetrics.horizontalAdvance(title) > titleRect.width()) {
            title = titleMetrics.elidedText(title, Qt::ElideMiddle, titleRect.width());
        }
        painter->drawText(titleRect, Qt::AlignLeft | Qt::AlignTop, title);
        painter->setPen(Qt::NoPen);

        auto descRect = QRect(bgRect.x() + 18, titleRect.bottom(), bgRect.width() - 36, 38);
        QColor descColor = QColor("#76718a");
        QPen descPen(descColor);
        painter->setPen(descPen);
        QFont descFont = painter->font();
        descFont.setPixelSize(12);
        descFont.setBold(false);
        painter->setFont(descFont);
        QString desc = data.desc;
        QTextOption toption(Qt::AlignLeft | Qt::AlignTop);
        toption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter->drawText(descRect, desc, toption);
        painter->setPen(Qt::NoPen);
    }
}

bool FuncItemDelegate::eventFilter(QObject *object, QEvent *event) {
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

QSize FuncItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return m_Size;
}