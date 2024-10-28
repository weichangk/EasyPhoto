/*
 * @Author: weick
 * @Date: 2024-03-23 10:48:38
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 08:00:39
 */

#pragma once
#include "imageerasewindow.h"
#include "models.h"
#include <QWidget>

namespace imageerase {
class ImageEraseController : public QObject {
    Q_OBJECT
public:
    explicit ImageEraseController();
    ~ImageEraseController();
    void showWindow();
    void closeWindow();

private:
    void init();
    void sigConnect();
    void openFileDialog(QWidget *parent = nullptr);
    void addData(const QStringList filePaths);
    void deleteData(const QString filePath);
    void clickedData(const QString filePath);
    void status(Status state);
    void start();
    void finished();
    void cancel();
    void deleteAll();
    void dataUpdate(Data data);
    bool checkAddedData(const QString filePath);
private:
    ImageEraseWindow *window_;
    QList<Data> datas_;
};
} // namespace imageerase