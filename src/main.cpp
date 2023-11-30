#include "mainwindow.h"
#include "acore/inc/alogmgr.h"
#include "acore/inc/astylemgr.h"
#include "acore/inc/alangmgr.h"
#include "awidget/inc/aapplication.h"

int main(int argc, char *argv[])
{
    AApplication a(argc, argv);
    qInstallMessageHandler(ALogMgr::outputMessage);
    AStyleMgr::setStyleToApp(":/res/style/app");
    // AStyleMgr::setStyleToApp(":/imagekit/res/style");
    ALangMgr::getInstance()->setSysLangLocale();
    MainWindow w;
    w.show();
    return a.exec();
}
