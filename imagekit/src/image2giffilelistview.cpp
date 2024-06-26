/*
 * @Author: weick
 * @Date: 2024-06-03 07:46:59
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-11 07:55:16
 */

#include "inc/image2giffilelistview.h"
#include "../acore/inc/apainterhelper.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include "inc/signals.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QScrollBar>
namespace image2gif {
inline QRect fileItemBorderRect(QRect itemRect) {
    return itemRect.adjusted(5, 3, -5, -3);
}

inline QRect fileItemThumbnailRect(QRect itemRect) {
    return itemRect.adjusted(5, 3, -5, -3);
}

inline QRect fileItemDeteleRect(QRect itemRect) {
    auto rc = fileItemBorderRect(itemRect);
    return QRect(rc.x() + rc.width() - 16 - 4, rc.y() + 4, 16, 16);
}

inline QRect fileItemIndexRect(QRect itemRect) {
    auto rc = fileItemBorderRect(itemRect);
    return QRect(rc.x() + 4, rc.y() + 4, rc.width() - 4, 24);
}

inline QRect fileItemBeforeAddRect(QRect itemRect) {
    auto rc = itemRect.adjusted(1, 1, -1, -1);
    return QRect(rc.x(), rc.y() + (rc.height() / 2) - 8, 16, 16);
}

inline QRect fileItemAfterAddRect(QRect itemRect) {
    auto rc = itemRect.adjusted(1, 1, -1, -1);
    return QRect(rc.x() + rc.width() - 16, rc.y() + (rc.height() / 2) - 8, 16, 16);
}

inline int isFileItemLeftOrRightRect(QRect itemRect, const QStyleOptionViewItem &option) {
    auto rc = itemRect;
    QPoint globalMousePos = QCursor::pos();
    const QAbstractItemView* view = qobject_cast<const QAbstractItemView*>(option.widget);
    if (view) {
        QPoint viewMousePos = view->viewport()->mapFromGlobal(globalMousePos);
        if (rc.adjusted(0, 0, 0 - rc.width() / 2, 0).contains(viewMousePos)) {
            return 1;
        } else if (rc.adjusted(0 + rc.width() / 2, 0, 0, 0).contains(viewMousePos)) {
            return 2;
        }
    }
    return 0;
}

Image2GifFileListModel::Image2GifFileListModel(QObject *parent) {
}

void Image2GifFileListModel::changeModels(const QList<Data> &datas) {
    beginResetModel();
    datas_ = datas;
    endResetModel();
}

void Image2GifFileListModel::changeData(int row, const Data &data) {
    beginResetModel();
    datas_[row] = data;
    endResetModel();
}

int Image2GifFileListModel::rowCount(const QModelIndex &parent) const {
    return datas_.count();
}

QVariant Image2GifFileListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= datas_.size()) {
        return QVariant();
    }
    if (role == Qt::UserRole) {
        return QVariant::fromValue(datas_[index.row()]);
    }
    return QVariant();
}

Qt::ItemFlags Image2GifFileListModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);
    if (index.isValid()) {
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    }
    return Qt::ItemIsDropEnabled | defaultFlags;
}

QStringList Image2GifFileListModel::mimeTypes() const {
    return {"application/x-myitemlist"};
}

QMimeData *Image2GifFileListModel::mimeData(const QModelIndexList &indexes) const {
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            Data item = datas_.at(index.row());
            stream << item.file_name << item.file_path << item.state << item.thumbnail << item.delete_icon;
        }
    }

    mimeData->setData("application/x-myitemlist", encodedData);
    return mimeData;
}

bool Image2GifFileListModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) {
    Q_UNUSED(column);
    Q_UNUSED(parent);

    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat("application/x-myitemlist"))
        return false;

    if (row < 0 || row >= datas_.size())
        row = datas_.size();

    QByteArray encodedData = data->data("application/x-myitemlist");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QList<Data> newItems;

    while (!stream.atEnd()) {
        Data item;
        int state;
        stream >> item.file_name >> item.file_path >> state >> item.thumbnail >> item.delete_icon;
        item.state = static_cast<Status>(state);
        newItems << item;
    }

    if (newItems.isEmpty())
        return false;

    // 获取拖拽的第一个项目
    Data draggedItem = newItems.first();

    // 找到原始位置
    int originalRow = -1;
    for (int i = 0; i < datas_.size(); ++i) {
        if (datas_.at(i).file_name == draggedItem.file_name && datas_.at(i).file_path == draggedItem.file_path && datas_.at(i).state == draggedItem.state) {
            originalRow = i;
            break;
        }
    }

    if (originalRow != -1) {
        // 使用parent.index获取目标位置
        int targetRow = parent.row();

        // 交换原始位置和目标位置的项目
        beginMoveRows(QModelIndex(), originalRow, originalRow, parent, row);
        datas_.swapItemsAt(originalRow, targetRow);
        endMoveRows();
    }

    return true;
}

Qt::DropActions Image2GifFileListModel::supportedDropActions() const {
    return Qt::CopyAction | Qt::MoveAction;
}

Image2GifFilesView::Image2GifFilesView(QWidget *parent) :
    QListView(parent) {
    setAttribute(Qt::WA_StyledBackground);
    setMouseTracking(true);
    setStyleSheet("border:0px; background-color:transparent;");
    setSpacing(0);
    setAcceptDrops(true);
    setDragEnabled(true);
    setDropIndicatorShown(true);
    setDefaultDropAction(Qt::MoveAction);
    setDragDropMode(QAbstractItemView::InternalMove);

    view_model_ = new Image2GifFileListModel(this);
    setModel(view_model_);

    // autoscroll_timer_ = new QTimer(this);
    // autoscroll_timer_->setInterval(50);
    // connect(autoscroll_timer_, &QTimer::timeout, this, &Image2GifFilesView::autoScroll);
}

void Image2GifFilesView::chageData(const QList<Data> &datas) {
    view_model_->changeModels(datas);
}

Data Image2GifFilesView::data(int i) const {
    return view_model_->data(view_model_->index(i, 0), Qt::UserRole).value<Data>();
}

int Image2GifFilesView::count() const {
    return view_model_->rowCount(QModelIndex());
}

void Image2GifFilesView::mousePressEvent(QMouseEvent* event) {
    QListView::mousePressEvent(event);
}

void Image2GifFilesView::mouseMoveEvent(QMouseEvent *event) {
    QListView::mouseMoveEvent(event);
    if (indexAt(event->pos()).row() != -1) {
        setCursor(Qt::PointingHandCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

void Image2GifFilesView::mouseReleaseEvent(QMouseEvent* event) {
    QListView::mouseReleaseEvent(event);
}

// void Image2GifFilesView::startDrag(Qt::DropActions supportedActions) {
//     autoscroll_timer_->start();
//     QListView::startDrag(supportedActions);
// }

// void Image2GifFilesView::dragMoveEvent(QDragMoveEvent *event) {
//     mouse_pos_ = event->pos();
//     QListView::dragMoveEvent(event);
// }

// void Image2GifFilesView::dragLeaveEvent(QDragLeaveEvent *event) {
//     autoscroll_timer_->stop();
//     QListView::dragLeaveEvent(event);
// }

void Image2GifFilesView::dropEvent(QDropEvent *event) {
    // 获取当前放置位置
    QModelIndex index = indexAt(event->pos());
    if (!index.isValid()) {
        // 如果放置位置无效，则忽略掉放置操作
        event->ignore();
        return;
    }

    // autoscroll_timer_->stop();
    QListView::dropEvent(event);
}

void Image2GifFilesView::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
}

// void Image2GifFilesView::autoScroll() {
//     const int margin = 20;     // 鼠标距离边缘的距离阈值
//     const int scrollSpeed = 5; // 滚动速度

//     if (mouse_pos_.y() < margin) {
//         // 向上滚动
//         verticalScrollBar()->setValue(verticalScrollBar()->value() - scrollSpeed);
//     } else if (mouse_pos_.y() > height() - margin) {
//         // 向下滚动
//         verticalScrollBar()->setValue(verticalScrollBar()->value() + scrollSpeed);
//     }

//     if (mouse_pos_.x() < margin) {
//         // 向左滚动
//         horizontalScrollBar()->setValue(horizontalScrollBar()->value() - scrollSpeed);
//     } else if (mouse_pos_.x() > width() - margin) {
//         // 向右滚动
//         horizontalScrollBar()->setValue(horizontalScrollBar()->value() + scrollSpeed);
//     }
// }

Image2GifFileItemDelegate::Image2GifFileItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

Image2GifFileItemDelegate::~Image2GifFileItemDelegate() {
}

bool Image2GifFileItemDelegate::eventFilter(QObject *object, QEvent *event) {
    int type = event->type();
    if (type == QEvent::MouseButtonPress || type == QEvent::MouseButtonRelease || type == QEvent::MouseMove) {
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

void Image2GifFileItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
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
    int isLeftOrRight = isFileItemLeftOrRightRect(rc, option);

    auto borderRect = fileItemBorderRect(rc);
    // painter->setBrush(QColor("#2F2D2D"));
    painter->drawRoundedRect(borderRect, 10, 10);
    painter->setBrush(Qt::NoBrush);

    auto pixmapRect = fileItemThumbnailRect(rc);
    APainterHelper::paintPixmap(painter, pixmapRect, data.thumbnail, 1, 10, true);

    if (hover) {
        auto delIconRect = fileItemDeteleRect(rc);
        APainterHelper::paintPixmap(painter, delIconRect, data.delete_icon, 1, 0, true);
    }

    if(isLeftOrRight == 1) {
        auto beforAddIconRect = fileItemBeforeAddRect(rc);
        APainterHelper::paintPixmap(painter, beforAddIconRect, data.before_add_icon, 1, 0, true);
    }
    if(isLeftOrRight == 2) {
        auto afterAddIconRect = fileItemAfterAddRect(rc);
        APainterHelper::paintPixmap(painter, afterAddIconRect, data.after_add_icon, 1, 0, true);
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
    auto indexRect = fileItemIndexRect(rc);
    painter->drawText(indexRect, Qt::PlainText, QString::number(index.row() + 1));
    painter->setPen(Qt::NoPen);
}

QSize Image2GifFileItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return size_;
}

void Image2GifFileItemDelegate::changeSizeHint(const QSize &size) {
    size_ = size;
}

Image2GifFileListView::Image2GifFileListView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

Image2GifFileListView::~Image2GifFileListView() {
}

void Image2GifFileListView::changeData(QList<Data> datas) {
    file_list_view_->chageData(datas);
}

void Image2GifFileListView::setCurrentIndex(int index) {
    file_list_view_->setCurrentIndex(file_list_view_->model()->index(index, 0));
}

int Image2GifFileListView::currentIndex() {
    return file_list_view_->currentIndex().row();
}

void Image2GifFileListView::createUi() {
    file_name_label_ = new ALabel(this);

    add_file_button_ = new APushButton(this);
    add_file_button_->setObjectName("OnlyIconButton");
    add_file_button_->setFixedSize(24, 24);
    add_file_button_->setIconSize(QSize(24, 24));
    add_file_button_->setIcon(QIcon(":/agui/res/image/setting-24.png"));

    delete_file_button_ = new APushButton(this);
    delete_file_button_->setObjectName("OnlyIconButton");
    delete_file_button_->setFixedSize(24, 24);
    delete_file_button_->setIconSize(QSize(24, 24));
    delete_file_button_->setIcon(QIcon(":/agui/res/image/setting-24.png"));

    auto buttonsWidget = new AWidget(this);
    buttonsWidget->setFixedHeight(32);
    auto buttonsLayout = new AHBoxLayout(buttonsWidget);
    buttonsLayout->addWidget(file_name_label_);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(add_file_button_);
    buttonsLayout->addWidget(delete_file_button_);

    file_list_view_ = new Image2GifFilesView(this);
    file_list_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    file_list_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    file_list_view_->setResizeMode(QListView::Adjust);
    file_list_view_->setViewMode(QListView::IconMode);
    file_list_view_->setSelectionMode(QAbstractItemView::SingleSelection);

    auto delegate = new Image2GifFileItemDelegate(this);
    file_list_view_->setItemDelegate(delegate);
    file_list_view_->viewport()->installEventFilter(delegate);

    auto mainLayout = new AVBoxLayout(this);
    mainLayout->addWidget(buttonsWidget);
    mainLayout->addWidget(file_list_view_, 1);
}

void Image2GifFileListView::changeLanguage() {
    file_name_label_->setText("文件名");
}

void Image2GifFileListView::sigConnect() {
    connect(add_file_button_, &APushButton::clicked, this, [=]() {
        emit Signals::getInstance()->sigOpenFileDialog(this);
    });
    connect(delete_file_button_, &APushButton::clicked, this, [=]() {
        emit Signals::getInstance()->sigDeleteAll();
    });
    connect(file_list_view_, &QListView::clicked, this, [=](const QModelIndex &index) {
        auto data = index.data(Qt::UserRole).value<Data>();
        QRect rc = file_list_view_->visualRect(index); // sizeHint大小，如果布局导致实际大小不是sizeHint大小时下面的位置计算就不对了
        int posx = file_list_view_->mapFromGlobal(QCursor::pos()).x();
        int posy = file_list_view_->mapFromGlobal(QCursor::pos()).y();
        QRect delIconRect = fileItemDeteleRect(rc);
        if (posx >= delIconRect.x() && posx <= delIconRect.x() + delIconRect.width()
            && posy >= delIconRect.y() && posy <= delIconRect.y() + delIconRect.height()) {
            emit Signals::getInstance()->sigDeleteFile(data.file_path);
            return;
        }
        QRect beforeAddRect = fileItemBeforeAddRect(rc);
        if (posx >= beforeAddRect.x() && posx <= beforeAddRect.x() + beforeAddRect.width()
            && posy >= beforeAddRect.y() && posy <= beforeAddRect.y() + beforeAddRect.height()) {
            emit Signals::getInstance()->sigListItemBeforeOrAfterAdd(index.row(), true, this);
            return;
        }
        QRect afterAddRect = fileItemAfterAddRect(rc);
        if (posx >= afterAddRect.x() && posx <= afterAddRect.x() + afterAddRect.width()
            && posy >= afterAddRect.y() && posy <= afterAddRect.y() + afterAddRect.height()) {
            emit Signals::getInstance()->sigListItemBeforeOrAfterAdd(index.row(), false, this);
            return;
        }
        emit Signals::getInstance()->sigClickedFile(data.file_path);
    });
}
} // namespace image2gif