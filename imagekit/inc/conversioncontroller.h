/*
 * @Author: weick
 * @Date: 2023-12-21 23:43:01
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-07 23:44:26
 */

#pragma once
#include "conversionwindow.h"
#include "conversionmodels.h"
#include <QWidget>

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
    void satrtConv();
    void switchChecked(const QString filePath, const bool checked);
    void allChecked(bool checked);
    void delByChecked();

private:
    ConversionWindow *m_ConversionWindow = 0;
    QList<ConversionData> m_ConvDatas;
};
