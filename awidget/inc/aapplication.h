#pragma once
#include "awidget_global.h"
#include <QApplication>

class AWIDGET_EXPORT AApplication : public QApplication
{
    Q_OBJECT
public:
    AApplication(int &argc, char **argv);

protected:
    bool event(QEvent *event) override;
    bool notify(QObject *, QEvent *) override;
};

