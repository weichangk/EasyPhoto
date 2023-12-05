/*
 * @Author: weick
 * @Date: 2023-12-05 23:05:39
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-05 23:20:43
 */

#include "mainwindow.h"
#include "../acore/inc/alogmgr.h"
#include "../acore/inc/astylemgr.h"
#include "../acore/inc/alangmgr.h"
#include "../agui/inc/aapplication.h"

int main(int argc, char *argv[]) {
    AApplication a(argc, argv);
    qInstallMessageHandler(ALogMgr::outputMessage);
    AStyleMgr::setStyleToApp(":/res/style");
    ALangMgr::getInstance()->setSysLangLocale();
    MainWindow w;
    w.show();
    return a.exec();
}
