#include "mainwindow.h"
#include "qapplication.h"
#include "stylemgr.h"
#include "fontmgr.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FontMgr::setFontToApp(QStringLiteral("微软雅黑"), 12);
    StyleMgr::setStyleToApp(":/resource/style/app");
    MainWindow w;
    w.show();
    return a.exec();
}
