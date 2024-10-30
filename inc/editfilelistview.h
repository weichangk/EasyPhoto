#pragma once
#include "inc/models.h"
#include "control/listview.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
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
    QSize size_ = QSize(260, 48);
    int event_type_ = QEvent::None;
    QPoint curpos_;
};

class EditFileListView : public QWidget {
    Q_OBJECT
public:
    explicit EditFileListView(QWidget *parent = nullptr);
    ~EditFileListView();
    void changeData(QList<Data> datas);
    void setCurrentIndex(int index);
    int currentIndex();

protected:
    void createUi();
    void sigConnect();

private:
    QLabel *file_name_label_ = nullptr;
    QPushButton *add_file_button_ = nullptr;
    QPushButton *delete_file_button_ = nullptr;
    ListView<Data> *file_list_view_ = nullptr;

    QList<Data> datas_;
};
} // namespace imageedit