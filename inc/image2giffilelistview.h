#pragma once
#include "inc/models.h"
#include "control/listview.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QAbstractListModel>
#include <QMimeData>
#include <QStyledItemDelegate>
#include <QListView>
#include <QMouseEvent>
#include <QEvent>

namespace image2gif {
class Image2GifFileListModel : public QAbstractListModel {
    Q_OBJECT
public:
    Image2GifFileListModel(QObject *parent);
    void changeModels(const QList<Data> &datas);
    void changeData(int row, const Data &data);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
    Qt::DropActions supportedDropActions() const override;

protected:
    QList<Data> datas_;
};

class Image2GifFilesView : public QListView {
    Q_OBJECT
public:
    Image2GifFilesView(QWidget *parent);
    void chageData(const QList<Data> &datas);
    Data data(int i) const;
    int count() const;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    // void startDrag(Qt::DropActions supportedActions) override;
    // void dragMoveEvent(QDragMoveEvent* event) override;
    // void dragLeaveEvent(QDragLeaveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;

private:
    // void autoScroll();

private:
    Image2GifFileListModel *view_model_ = 0;

    QPoint mouse_pos_;
    QTimer* autoscroll_timer_;
};

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

class Image2GifFileListView : public QWidget {
    Q_OBJECT
public:
    explicit Image2GifFileListView(QWidget *parent = nullptr);
    ~Image2GifFileListView();
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
    Image2GifFilesView *file_list_view_ = nullptr;

};
} // namespace image2gif