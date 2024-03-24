/*
 * @Author: weick
 * @Date: 2024-03-23 11:10:19
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 12:34:40
 */

#include "inc/editfilelistview.h"
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
}

EditFileListView::~EditFileListView() {
}

void EditFileListView::createUi() {
    list_widget = new QListWidget(this);
    list_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    list_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list_widget->setAttribute(Qt::WA_StyledBackground);
    list_widget->setResizeMode(QListView::Adjust);
    list_widget->setViewMode(QListView::ListMode);
    list_widget->setFlow(QListView::TopToBottom);
    list_widget->setSelectionMode(QAbstractItemView::SingleSelection);
    list_widget->setMouseTracking(true);
    list_widget->setStyleSheet("border:0px; background-color:transparent;");
    list_widget->setSpacing(0);
    
    auto mainLayout = new AVBoxLayout(this);
    mainLayout->addWidget(list_widget);
}

void EditFileListView::changeLanguage() {
} 

void EditFileListView::sigConnect() {
}
} // namespace imageedit