#include "mainwindow.h"
#include "qapplication.h"
#include "acore/logmgr.h"
#include "acore/fontmgr.h"
#include "acore/stylemgr.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(LogMgr::outputMessage);
    FontMgr::setFontToApp(QStringLiteral("微软雅黑"), 12);
    StyleMgr::setStyleToApp(":/resource/style/app");
    MainWindow w;
    w.show();
    return a.exec();
}
