/*
 * @Author: weick 
 * @Date: 2024-06-04 08:00:19 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-04 08:00:19 
 */

#pragma once
#include "imageenhancementwindow.h"
#include "models.h"
#include <QWidget>

namespace imageenhancement {
class ImageEnhancementController : public QObject {
    Q_OBJECT
public:
    explicit ImageEnhancementController();
    ~ImageEnhancementController();
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
    ImageEnhancementWindow *window_;
    QList<Data> datas_;
};
} // namespace imageenhancement