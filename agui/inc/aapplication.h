#pragma once
#include "agui_global.h"
#include <QApplication>

class AGUI_EXPORT AApplication : public QApplication
{
    Q_OBJECT
public:
    AApplication(int &argc, char **argv);

protected:
    bool event(QEvent *event) override;
    bool notify(QObject *, QEvent *) override;
};

