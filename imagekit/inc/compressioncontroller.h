/*
 * @Author: weick
 * @Date: 2024-01-07 23:43:32
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 22:07:34
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
    void compressStatus(imagecompression::Status state);
    void compressStart();
    void compressFinished();
    void compressCancel();
    void switchChecked(const QString filePath, const bool checked);
    void allChecked(bool checked);
    void delByChecked();
private:
    CompressionWindow *m_CompressionWindow = 0;
    QList<imagecompression::Data> m_CompressDatas;
};
