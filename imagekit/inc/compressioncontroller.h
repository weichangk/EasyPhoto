/*
 * @Author: weick
 * @Date: 2024-01-07 23:43:32
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-07 23:48:44
 */

#pragma once
#include "compressionwindow.h"
#include "models.h"
#include <QWidget>

class CompressionController : public QObject {
    Q_OBJECT
public:
    explicit CompressionController();
    ~CompressionController();
    void showWindow();
    void closeWindow();

private:
    void init();
    void sigConnect();
    void openCompressFileDialog(QWidget *parent = 0);
    void addCompressData(const QStringList filePaths);
    void delCompressData(const QString filePath);
    void compressStatus(Models::CompressStatusEnum state);
    void compressStart();
    void compressFinished();
    void compressCancel();
    void switchChecked(const QString filePath, const bool checked);
    void allChecked(bool checked);
    void delByChecked();

    //
    void compressPNG(const QString input, const QString out, const int quatily);
    void compressJPEG(const QString input, const QString out, const int quatily);
    void compressWEBP(const QString input, const QString out, const int quatily);
    void compressGIF(const QString input, const QString out, const int quatily);

private:
    CompressionWindow *m_CompressionWindow = 0;
    QList<Models::CompressionData> m_CompressDatas;
};
