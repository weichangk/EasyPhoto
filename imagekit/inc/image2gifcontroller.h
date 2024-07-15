/*
 * @Author: weick
 * @Date: 2024-03-23 10:48:38
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 08:00:39
 */

#pragma once
#include "image2gifwindow.h"
#include "models.h"
#include <QWidget>

namespace image2gif {
class Image2GifController : public QObject {
    Q_OBJECT
public:
    explicit Image2GifController();
    ~Image2GifController();
    void showWindow();
    void closeWindow();

private:
    void init();
    void sigConnect();
    void openFileDialog(QWidget *parent = nullptr);
    void appendData(const QStringList filePaths);
    void insertData(int index, const QStringList filePaths);
    void deleteData(const QString filePath);
    void clickedData(const QString filePath);
    void status(Status state);
    void start();
    void finished();
    void cancel();
    void deleteAll();
    void dataUpdate(Data data);
    bool checkAddedData(const QString filePath);
    void listItemBeforeOrAfterAdd(int index, bool isBefore, QWidget *parent = nullptr);
    void listItemSwapedUpdateDatas(const QList<Data> &datas);
    void generate(bool isExport);
    void slotExportStart();
    void slotExportEnd(bool state, const QString &filePath, const QString &error);
    void slotPreviewStart();
    void slotPreviewEnd(bool state, const QString &filePath, const QString &error);
private:
    Image2GifWindow *window_;
    QList<Data> datas_;
};
} // namespace image2gif