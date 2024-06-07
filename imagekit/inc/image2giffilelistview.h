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

namespace image2gif {
class Image2GifFileItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit Image2GifFileItemDelegate(QObject *parent = nullptr);
    ~Image2GifFileItemDelegate();

    bool eventFilter(QObject *object, QEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void changeSizeHint(const QSize &size);

private:
    QSize size_ = QSize(120, 90);
    int event_type_ = QEvent::None;
    QPoint curpos_;
};

class Image2GifFileListView : public ABaseWidget {
    Q_OBJECT
public:
    explicit Image2GifFileListView(QWidget *parent = nullptr);
    ~Image2GifFileListView();
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
} // namespace image2gif