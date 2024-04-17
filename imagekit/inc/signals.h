/*
 * @Author: weick
 * @Date: 2023-12-09 23:45:45
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 21:23:44
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
};

namespace imageconversion {
class Signals : public QObject, public ASinglton<Signals> {
    Q_OBJECT
public:
Q_SIGNALS:
    void sigOpenFileDialog(QWidget *parent = 0);
    void sigAddFile();
    void sigDeleteFile(const QString filePath);
    void sigDeleteByChecked();
    void sigStatus(Status state);
    void sigStatus2View(Status state);
    void sigSwitchChecked(const QString filePath, const bool checked);
    void sigCheckedAll(const bool checked);
    void sigChangeFormat(const QString format);
};
} // namespace imageconversion

namespace imagecompression {
class Signals : public QObject, public ASinglton<Signals> {
    Q_OBJECT
public:
Q_SIGNALS:
    void sigOpenFileDialog(QWidget *parent = 0);
    void sigAddFile();
    void sigDeleteFile(const QString filePath);
    void sigDeleteByChecked();
    void sigStatus(Status state);
    void sigStatus2View(Status state);
    void sigSwitchChecked(const QString filePath, const bool checked);
    void sigCheckedAll(const bool checked);
    void sigChangeFormat(const QString format);
};
} // namespace imagecompression

namespace imageedit {
class Signals : public QObject, public ASinglton<Signals> {
    Q_OBJECT
public:
Q_SIGNALS:
    void sigWindowMove();
    void sigOpenFileDialog(QWidget *parent = nullptr);
    void sigDeleteFile(const QString filePath);
    void sigDeleteByChecked();
    void sigDeleteAll();
    void sigStatus(Status state);
    void sigSwitchChecked(const QString filePath, const bool checked);
    void sigCheckedAll(const bool checked);
};
} // namespace imageedit