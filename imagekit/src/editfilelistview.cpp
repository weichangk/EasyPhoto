/*
 * @Author: weick
 * @Date: 2024-03-23 11:10:19
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 13:54:45
 */

#include "inc/editfilelistview.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"

namespace imageedit {
EditFileItemDelegate::EditFileItemDelegate(QObject *parent) {
}

EditFileItemDelegate::~EditFileItemDelegate() {
}

void EditFileItemDelegate::paint(QPainter *painter,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const {
}

EditFileListView::EditFileListView(QWidget *parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

EditFileListView::~EditFileListView() {
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
    
    list_widget_ = new QListWidget(this);
    list_widget_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    list_widget_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list_widget_->setAttribute(Qt::WA_StyledBackground);
    list_widget_->setResizeMode(QListView::Adjust);
    list_widget_->setViewMode(QListView::ListMode);
    list_widget_->setFlow(QListView::TopToBottom);
    list_widget_->setSelectionMode(QAbstractItemView::SingleSelection);
    list_widget_->setMouseTracking(true);
    list_widget_->setStyleSheet("border:0px; background-color:transparent;");
    list_widget_->setSpacing(0);
    
    auto mainLayout = new AVBoxLayout(this);
    mainLayout->addWidget(buttonsWidget);
    mainLayout->addWidget(list_widget_, 1);
}

void EditFileListView::changeLanguage() {
} 

void EditFileListView::sigConnect() {
}
} // namespace imageedit