/*
 * @Author: weick
 * @Date: 2024-03-23 11:06:40
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-29 22:31:24
 */

#pragma once
#include "../awidget/inc/apushbutton.h"
#include "../agui/inc/acheckedbutton.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/alistview.h"
#include "inc/models.h"
#include <QListWidget>
#include <QStyledItemDelegate>
#include <QEvent>

namespace imageedit {
class EditFileItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit EditFileItemDelegate(QObject *parent = nullptr);
    ~EditFileItemDelegate();

    bool eventFilter(QObject *object, QEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void changeSizeHint(const QSize &size);

private:
    QSize size_ = QSize(300, 48);
    int event_type_ = QEvent::None;
    QPoint curpos_;
};

class EditFileListView : public ABaseWidget {
    Q_OBJECT
public:
    explicit EditFileListView(QWidget *parent = nullptr);
    ~EditFileListView();
    void changeData(QList<Data> datas);
    void setCurrentIndex(int index);

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    ACheckedButton *all_select_button_ = nullptr;
    APushButton *add_file_button_ = nullptr;
    APushButton *delete_file_button_ = nullptr;
    AListView<Data> *file_list_view_ = nullptr; 

    QList<Data> datas_;
    bool is_all_select_button_click = false;
};
} // namespace imageedit