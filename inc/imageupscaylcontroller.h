#pragma once
#include "imageupscaylwindow.h"
#include "models.h"
#include <QWidget>

namespace imageupscayl {
class ImageUpscaylController : public QObject {
    Q_OBJECT
public:
    explicit ImageUpscaylController();
    ~ImageUpscaylController();
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
    ImageUpscaylWindow *window_;
    QList<Data> datas_;
};
} // namespace imageupscayl