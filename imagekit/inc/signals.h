/*
 * @Author: weick
 * @Date: 2023-12-09 23:45:45
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-10 14:39:42
 */

#pragma once
#include "../acore/inc/asinglton.h"
#include "models.h"
#include <QWidget>

class Signals : public QObject, public ASinglton<Signals>
{
    Q_OBJECT
public:
    Q_SIGNALS:
    void sigGotoFunc(Models::Funcs func);

    //Conversion
    void sigOpenConvFileDialog(QWidget *parent = 0);
    void sigAddConvFile();
    void sigDelConvFile(const QString path);
    void sigSatrtConv();
};
