/*
 * @Author: weick
 * @Date: 2023-12-09 23:45:45
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 20:20:15
 */

#pragma once
#include "../acore/inc/asinglton.h"
#include "models.h"
#include <QWidget>

class Signals : public QObject, public ASinglton<Signals> {
    Q_OBJECT
public:
Q_SIGNALS:
    void sigGotoFunc(ImageFunc func);

    // Conversion
    void sigOpenConvFileDialog(QWidget *parent = 0);
    void sigAddConvFile();
    void sigDelConvFile(const QString filePath);
    void sigDelByChecked();
    void sigConvStatus(imageconversion::Status state);
    void sigSwitchChecked(const QString filePath, const bool checked);
    void sigAllChecked(const bool checked);
    void sigChangeConvFormat(const QString format);

    void sigConvStatus_v(imageconversion::Status state);

    // Compress
    void sigCompressOpenFileDialog(QWidget *parent = 0);
    void sigCompressAddFile();
    void sigCompressDelFile(const QString filePath);
    void sigCompressDelByChecked();
    void sigCompressStatus(imagecompression::Status state);
    void sigCompressStatusToView(imagecompression::Status state);
    void sigCompressSwitchChecked(const QString filePath, const bool checked);
    void sigCompressAllChecked(const bool checked);
    void sigChangeCompressFormat(const QString format);
};

namespace imageedit {
class Signals : public QObject, public ASinglton<Signals> {
    Q_OBJECT
public:
Q_SIGNALS:
    void sigOpenFileDialog(QWidget *parent = nullptr);
    void sigDeleteFile(const QString filePath);
    void sigDeleteByChecked();
    void sigStatus(Status state);
    void sigSwitchChecked(const QString filePath, const bool checked);
    void sigCheckedAll(const bool checked);
};
}