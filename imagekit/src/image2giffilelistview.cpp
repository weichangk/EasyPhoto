/*
 * @Author: weick 
 * @Date: 2024-06-03 07:46:59 
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:48:46
 */

#include "inc/image2giffilelistview.h"
#include "../acore/inc/apainterhelper.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include "inc/signals.h"
#include <QPainter>
#include <QMouseEvent>

namespace image2gif {
inline QRect fileItemDeteleRect(QRect itemRect) {
    auto rc = itemRect.adjusted(1, 1, -1, -1);
    return QRect(rc.x() + rc.width() - 16 - 16, rc.y() + 16, 16, 16);
}

inline QRect fileItemNameRect(QRect itemRect) {
    auto rc = itemRect;
    auto deleteRect = fileItemDeteleRect(rc);
    int nameX = rc.x() + 16;
    int nameWidth = deleteRect.x() - 16 - nameX;
    return QRect(nameX, rc.y() + 12, nameWidth, 24);
}

Image2GifFileItemDelegate::Image2GifFileItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

Image2GifFileItemDelegate::~Image2GifFileItemDelegate() {
}

bool Image2GifFileItemDelegate::eventFilter(QObject *object, QEvent *event) {
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

    auto borderRect = rc.adjusted(1, 1, -1, -1);
    painter->setBrush(QColor("#2F2D2D"));
    painter->drawRoundedRect(borderRect, 0, 0);
    painter->setBrush(Qt::NoBrush);

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

    file_list_view_ = new AListView<Data>(this);
    file_list_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    file_list_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    file_list_view_->setResizeMode(QListView::Adjust);
    file_list_view_->setViewMode(QListView::ListMode);
    file_list_view_->setFlow(QListView::TopToBottom);
    file_list_view_->setDragEnabled(false);
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
        emit Signals::getInstance()->sigClickedFile(data.file_path);
    });
}
} // namespace imageimage2gif