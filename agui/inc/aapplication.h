/*
 * @Author: weick
 * @Date: 2023-12-05 22:50:25
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 22:50:25
 */

#pragma once
#include "agui_global.h"
#include <QApplication>

class AGUI_EXPORT AApplication : public QApplication {
    Q_OBJECT
public:
    AApplication(int &argc, char **argv);

protected:
    bool event(QEvent *event) override;
    bool notify(QObject *, QEvent *) override;
};
