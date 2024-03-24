/*
 * @Author: weick
 * @Date: 2024-03-23 10:48:38
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 20:04:42
 */

#pragma once
#include "editwindow.h"
#include "models.h"
#include <QWidget>

namespace imageedit {
class EditController : public QObject {
    Q_OBJECT
public:
    explicit EditController();
    ~EditController();
    void showWindow();
    void closeWindow();

private:
    void init();
    void sigConnect();
    void openFileDialog(QWidget *parent = nullptr);
    void addData(const QStringList filePaths);
    void deleteData(const QString filePath);
    void status(Status state);
    void start();
    void finished();
    void cancel();
    void switchChecked(const QString filePath, const bool checked);
    void checkedAll(bool checked);
    void deleteByChecked();
private:
    EditWindow *window_;
    QList<Data> datas_;
};
} // namespace imageedit