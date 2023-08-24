#include "mainwindow.h"
#include "stylemgr.h"
#include <QApplication>
#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StyleMgr::setStyleToAppByCssFolder(":/resources/qss/global");
    MainWindow w;
    w.show();
    return a.exec();
}
