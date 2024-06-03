/*
 * @Author: weick
 * @Date: 2024-06-03 07:36:53
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:38:23
 */

#pragma once
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/alabel.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/alistview.h"
#include "inc/models.h"
#include <QListWidget>
#include <QStyledItemDelegate>
#include <QEvent>

namespace imageerase {
class ImageEraseFileItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ImageEraseFileItemDelegate(QObject *parent = nullptr);
    ~ImageEraseFileItemDelegate();

    bool eventFilter(QObject *object, QEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void changeSizeHint(const QSize &size);

private:
    QSize size_ = QSize(260, 48);
    int event_type_ = QEvent::None;
    QPoint curpos_;
};

class ImageEraseFileListView : public ABaseWidget {
    Q_OBJECT
public:
    explicit ImageEraseFileListView(QWidget *parent = nullptr);
    ~ImageEraseFileListView();
    void changeData(QList<Data> datas);
    void setCurrentIndex(int index);
    int currentIndex();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    ALabel *file_name_label_ = nullptr;
    APushButton *add_file_button_ = nullptr;
    APushButton *delete_file_button_ = nullptr;
    AListView<Data> *file_list_view_ = nullptr;

    QList<Data> datas_;
};
} // namespace imageerase