/*
 * @Author: weick
 * @Date: 2023-12-21 23:43:01
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 23:04:17
 */

#pragma once
#include "conversionwindow.h"
#include "models.h"
#include <QWidget>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>

class ConversionController : public QObject {
    Q_OBJECT
public:
    explicit ConversionController();
    ~ConversionController();
    void showWindow();
    void closeWindow();

private:
    void init();
    void sigConnect();
    void openConvFileDialog(QWidget *parent = 0);
    void addConvData(const QStringList filePaths);
    void delConvData(const QString filePath);
    void convStatus(imageconversion::Status state);
    void startConv();
    void finishedConv();
    void cancelConv();
    void switchChecked(const QString filePath, const bool checked);
    void allChecked(bool checked);
    void delByChecked();
    void changeConvFormat(const QString format);

private:
    ConversionWindow *m_ConversionWindow = 0;
    QList<imageconversion::Data> m_ConvDatas;
    QStringList m_FormatDatas;

    QFutureWatcher<void> m_ConvWatcher;
};
