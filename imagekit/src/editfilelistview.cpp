/*
 * @Author: weick
 * @Date: 2024-03-23 11:10:19
 * @Last Modified by: weick
 * @Last Modified time: 2024-04-02 07:49:02
 */

#include "inc/editfilelistview.h"
#include "../acore/inc/apainterhelper.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include "inc/signals.h"
#include <QPainter>
#include <QMouseEvent>

namespace imageedit {
inline QRect fileItemCheckedRect(QRect itemRect) {
    auto rc = itemRect.adjusted(1, 1, -1, -1);
    return QRect(rc.x() + 16, rc.y() + 16, 16, 16);
}

inline QRect fileItemDeteleRect(QRect itemRect) {
    auto rc = itemRect.adjusted(1, 1, -1, -1);
    return QRect(rc.x() + rc.width() - 16 - 16, rc.y() + 16, 16, 16);
}

inline QRect fileItemNameRect(QRect itemRect) {
    auto rc = itemRect;
    auto checkedRect = fileItemCheckedRect(rc);
    auto deleteRect = fileItemDeteleRect(rc);
    int nameX = checkedRect.x() + checkedRect.width() + 8;
    int nameWidth = deleteRect.x() - 8 - nameX;
    return QRect(nameX, rc.y() + 12, nameWidth, 24);
}

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

    // auto checkedRect = fileItemCheckedRect(rc);
    // APainterHelper::paintPixmap(painter, checkedRect, data.is_checked ? data.checked_icon : data.unchecked_icon, 1, 0, true);

    if (hover) {
        auto delIconRect = fileItemDeteleRect(rc);
        APainterHelper::paintPixmap(painter, delIconRect, data.delete_icon, 1, 0, true);
    }

    QPen pen(QColor("#1F1F1F"));
    pen.setWidth(1);
    painter->setPen(pen);
    if (hover || pressed) {
        painter->drawRoundedRect(borderRect, 0, 0);
    }
    painter->setPen(Qt::NoPen);

    pen.setColor(Qt::blue);
    painter->setPen(pen);
    if (selected) {
        painter->drawRoundedRect(borderRect, 0, 0);
    }
    painter->setPen(Qt::NoPen);

    pen.setColor(QColor("#575859"));
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPointSizeF(11);
    painter->setFont(font);
    QString fileName = data.file_name;
    auto nameRect = fileItemNameRect(rc);
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

EditFileListView::EditFileListView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

EditFileListView::~EditFileListView() {
}

void EditFileListView::changeData(QList<Data> datas) {
    file_list_view_->chageData(datas);

    bool isAllChecked = datas.count() > 0;
    for (const auto &data : datas) {
        if (!data.is_checked) {
            isAllChecked = false;
            break;
        }
    }
    if (!is_all_select_button_click) {
        all_select_button_->setCheck(isAllChecked);
    }
}

void EditFileListView::setCurrentIndex(int index) {
    file_list_view_->setCurrentIndex(file_list_view_->model()->index(index, 0));
}

void EditFileListView::createUi() {
    add_file_button_ = new APushButton(this);
    add_file_button_->setObjectName("OnlyIconButton");
    add_file_button_->setFixedSize(24, 24);
    add_file_button_->setIconSize(QSize(24, 24));
    add_file_button_->setIcon(QIcon(":/agui/res/image/setting-24.png"));

    all_select_button_ = new ACheckedButton(this);
    all_select_button_->setIconSize(QSize(24, 24));

    delete_file_button_ = new APushButton(this);
    delete_file_button_->setObjectName("OnlyIconButton");
    delete_file_button_->setFixedSize(24, 24);
    delete_file_button_->setIconSize(QSize(24, 24));
    delete_file_button_->setIcon(QIcon(":/agui/res/image/setting-24.png"));

    auto buttonsWidget = new AWidget(this);
    buttonsWidget->setFixedHeight(32);
    auto buttonsLayout = new AHBoxLayout(buttonsWidget);
    buttonsLayout->addWidget(all_select_button_);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(add_file_button_);
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
    all_select_button_->setText("文件名");
}

void EditFileListView::sigConnect() {
    connect(all_select_button_, &ACheckedButton::clicked, this, [=](bool isChecked) {
        is_all_select_button_click = true;
        emit Signals::getInstance()->sigCheckedAll(isChecked);
        is_all_select_button_click = false;
    });
    connect(add_file_button_, &APushButton::clicked, this, [=]() {
        emit Signals::getInstance()->sigOpenFileDialog(this);
    });
    connect(delete_file_button_, &APushButton::clicked, this, [=]() {
        emit Signals::getInstance()->sigDeleteAll();
    });
    connect(file_list_view_, &QListView::clicked, this, [=](const QModelIndex &index) {
        auto data = index.data(Qt::UserRole).value<Data>();
        QRect rc = file_list_view_->visualRect(index);
        int posx = file_list_view_->mapFromGlobal(QCursor::pos()).x();
        int posy = file_list_view_->mapFromGlobal(QCursor::pos()).y();
        QRect delIconRect = fileItemDeteleRect(rc);
        if (posx >= delIconRect.x() && posx <= delIconRect.x() + delIconRect.width()
            && posy >= delIconRect.y() && posy <= delIconRect.y() + delIconRect.height()) {
            emit Signals::getInstance()->sigDeleteFile(data.file_path);
        }
        // auto checkedRect = fileItemCheckedRect(rc);
        // if (posx >= checkedRect.x() && posx <= checkedRect.x() + checkedRect.width()
        //     && posy >= checkedRect.y() && posy <= checkedRect.y() + checkedRect.height()) {
        //     emit Signals::getInstance()->sigSwitchChecked(data.file_path, data.is_checked);
        // }
    });
    
    // connect(file_list_view_->model(), &QAbstractItemModel::currentChanged, [&listView](const QModelIndex &current, const QModelIndex &previous) {
    //     // 更新 QListView 的当前选项
    //     listView.setCurrentIndex(current);
    // });
}
} // namespace imageedit