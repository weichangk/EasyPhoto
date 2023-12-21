/*
 * @Author: weick
 * @Date: 2023-12-21 23:43:01
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-21 23:57:17
 */

#pragma once
#include "../acore/inc/asinglton.h"
#include <QObject>

class ConversionController : public QObject, public ASinglton<ConversionController> {
    Q_OBJECT
public:

protected:
    explicit ConversionController();
    ~ConversionController();
};
