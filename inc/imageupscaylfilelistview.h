#pragma once
#include "inc/models.h"
#include "control/listview.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QStyledItemDelegate>
#include <QEvent>

namespace imageupscayl {
class ImageUpscaylFileItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ImageUpscaylFileItemDelegate(QObject *parent = nullptr);
    ~ImageUpscaylFileItemDelegate();

    bool eventFilter(QObject *object, QEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void changeSizeHint(const QSize &size);

private:
    QSize size_ = QSize(260, 48);
    int event_type_ = QEvent::None;
    QPoint curpos_;
};

class ImageUpscaylFileListView : public QWidget {
    Q_OBJECT
public:
    explicit ImageUpscaylFileListView(QWidget *parent = nullptr);
    ~ImageUpscaylFileListView();
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
} // namespace imageupscayl