/*
 * @Author: weick
 * @Date: 2024-03-23 11:06:40
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 13:24:36
 */

#pragma once
#include "../awidget/inc/apushbutton.h"
#include "../agui/inc/abasewidget.h"
#include <QListWidget>
#include <QAbstractItemDelegate>

namespace imageedit {
class EditFileItemDelegate : public QAbstractItemDelegate {
    Q_OBJECT
public:
    EditFileItemDelegate(QObject *parent = nullptr);
    ~EditFileItemDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

class EditFileListView : public ABaseWidget {
    Q_OBJECT
public:
    explicit EditFileListView(QWidget *parent = nullptr);
    ~EditFileListView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    APushButton *add_file_button_ = nullptr;
    APushButton *add_folder_button_ = nullptr;
    APushButton *delete_file_button_ = nullptr;
    QListWidget *list_widget_ = nullptr;
};
} // namespace imageedit