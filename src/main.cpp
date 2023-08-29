#include "mainwindow.h"
#include "qapplication.h"
#include "acore/logmgr.h"
#include "acore/stylemgr.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(LogMgr::outputMessage);
    // StyleMgr::setStyleToApp(":/resource/style/app");
    MainWindow w;
    w.show();
    return a.exec();
}
