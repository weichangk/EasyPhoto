/*
 * @Author: weick
 * @Date: 2024-03-23 11:10:19
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 13:54:45
 */

#include "inc/editfilelistview.h"
#include "../acore/inc/apainterhelper.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include <QPainter>
#include <QMouseEvent>

namespace imageedit {
EditFileItemDelegate::EditFileItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

EditFileItemDelegate::~EditFileItemDelegate() {
}

bool EditFileItemDelegate::eventFilter(QObject *object, QEvent *event) {
    int type = event->type();
    if (type == QEvent::MouseButtonPress || type == QEvent::MouseButtonRelease) {
        event_type_ = type;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent) {
            QPoint pos = mouseEvent->pos();
            curpos_ = pos;
            QWidget *curWidget = static_cast<QWidget *>(object);
            curWidget->update();
        }
    }
    return QStyledItemDelegate::eventFilter(object, event);
}

void EditFileItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<Data>();
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);

    QRect rc = option.rect;
    bool pressed = event_type_ == QEvent::MouseButtonPress && rc.contains(curpos_);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto borderRect = rc.adjusted(1, 1, -1, -1);
    painter->setBrush(QColor("#2F2D2D"));
    painter->drawRoundedRect(borderRect, 0, 0);
    painter->setBrush(Qt::NoBrush);

    auto checkedconRect = QRect(borderRect.x() + 24, borderRect.y() + 12, data.checked_icon.width(), data.checked_icon.height());
    APainterHelper::paintPixmap(painter, checkedconRect, data.is_checked ? data.checked_icon : data.unchecked_icon, 1, 0, true);

    if (hover) {
        auto delIconRect = QRect(borderRect.x() + borderRect.width() - data.delete_icon.width() - 24, borderRect.y() + 12, data.delete_icon.width(), data.delete_icon.height());
        APainterHelper::paintPixmap(painter, delIconRect, data.delete_icon, 1, 0, true);
    }

    QPen pen(QColor("#1F1F1F"));
    // pen.setWidth(1);
    // painter->setPen(pen);
    // if (hover || pressed) {
    //     painter->drawRoundedRect(borderRect, 10, 10);
    // }
    painter->setPen(Qt::NoPen);

    pen.setColor(QColor("#575859"));
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPointSizeF(11);
    painter->setFont(font);
    QString fileName = data.file_name;
    auto nameRect = QRect(borderRect.x() + (24 * 3), borderRect.y() + 12, borderRect.width() - (24 * 6), 24);
    QFontMetricsF metrics(font);
    if (metrics.horizontalAdvance(fileName) > nameRect.width()) {
        fileName = metrics.elidedText(fileName, Qt::ElideMiddle, nameRect.width(), Qt::TextShowMnemonic);
    }
    painter->drawText(nameRect, Qt::PlainText, fileName);
    painter->setPen(Qt::NoPen);
}

QSize EditFileItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return size_;
}

void EditFileItemDelegate::changeSizeHint(const QSize &size) {
    size_ = size;
}

EditFileListView::EditFileListView(QWidget *parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

EditFileListView::~EditFileListView() {
}

void EditFileListView::changeData(QList<Data> datas) {
    file_list_view_->chageData(datas);
}

void EditFileListView::createUi() {
    add_file_button_ = new APushButton(this);
    add_file_button_->setObjectName("OnlyIconButton");
    add_file_button_->setFixedSize(24, 24);
    add_file_button_->setIconSize(QSize(24, 24));
    add_file_button_->setIcon(QIcon(":/agui/res/image/setting-24.png"));

    add_folder_button_ = new APushButton(this);
    add_folder_button_->setObjectName("OnlyIconButton");
    add_folder_button_->setFixedSize(24, 24);
    add_folder_button_->setIconSize(QSize(24, 24));
    add_folder_button_->setIcon(QIcon(":/agui/res/image/setting-24.png"));

    delete_file_button_ = new APushButton(this);
    delete_file_button_->setObjectName("OnlyIconButton");
    delete_file_button_->setFixedSize(24, 24);
    delete_file_button_->setIconSize(QSize(24, 24));
    delete_file_button_->setIcon(QIcon(":/agui/res/image/setting-24.png"));

    auto buttonsWidget = new AWidget(this);
    buttonsWidget->setFixedHeight(32);
    auto buttonsLayout = new AHBoxLayout(buttonsWidget);
    buttonsLayout->addWidget(add_file_button_);
    buttonsLayout->addWidget(add_folder_button_);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(delete_file_button_);
    
    file_list_view_ = new AListView<Data>(this);
    file_list_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    file_list_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    file_list_view_->setResizeMode(QListView::Adjust);
    file_list_view_->setViewMode(QListView::ListMode);
    file_list_view_->setFlow(QListView::TopToBottom);
    file_list_view_->setSelectionMode(QAbstractItemView::SingleSelection);

    auto delegate = new EditFileItemDelegate(this);
    file_list_view_->setItemDelegate(delegate);
    file_list_view_->viewport()->installEventFilter(delegate);

    auto mainLayout = new AVBoxLayout(this);
    mainLayout->addWidget(buttonsWidget);
    mainLayout->addWidget(file_list_view_, 1);
}

void EditFileListView::changeLanguage() {
} 

void EditFileListView::sigConnect() {
}
} // namespace imageedit