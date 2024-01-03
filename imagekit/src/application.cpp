/*
 * @Author: weick
 * @Date: 2023-12-05 23:02:58
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-10 14:56:50
 */

#include "inc/application.h"
#include "inc/startupcontroller.h"
#include "inc/models.h"
#include "../acore/inc/astylemgr.h"
#include <Magick++.h>

using namespace Magick;

Application::Application(int argc, char *argv[]) :
    QApplication(argc, argv) {
    setOrganizationName(ORGANIZATION_NAME);
    setOrganizationDomain(ORGANIZATION_DOMAIN);
    setApplicationName(APPLICATION_NAME);
    setApplicationDisplayName(APPLICATION_DISPLAY_NAME);
    // setQuitOnLastWindowClosed(false);
    AStyleMgr::setStyleToApp(":/res/style");
    initUi();
    // InitializeMagick(*argv);
}

void Application::initUi() {
    // UseHighDpiPixmaps is default from Qt6
#if QT_VERSION < 0x060000
    setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif
    // QString icoLocalPath = QCoreApplication::applicationDirPath() + '/' + QStringLiteral(PROJECT_ICON_NAME);
    // QString icoSysPath = QStringLiteral(PROJECT_ICON_SYSTEM_PATH);

    // // Try first to find the app icon in the current/build directory
    // appIcon_ = QIcon(icoLocalPath);
    // if (appIcon_.isNull())
    //     appIcon_ = QIcon(icoSysPath);

    m_Settings.load();

    m_StartupController = new StartupController;
    // m_StartupWindow->setWindowIcon(appIcon_);
    // m_StartupWindow->setWindowTitle(applicationDisplayName());
    m_StartupController->showFunc(Models::Funcs::Startup); // FIXME: crash without this

    // trayIcon_->setIcon(appIcon_);
    // trayIcon_->setWidget(mainWindow_);

    // connect(this, &QApplication::aboutToQuit, trayIcon_, &QObject::deleteLater);
    // connect(this, &QApplication::aboutToQuit, mainWindow_, &QObject::deleteLater);
    // connect(this, &QApplication::aboutToQuit, this, [this]() {
    //     mainWindow_->saveSettings();
    //     m_Settings.save();
    // });
}

int main(int argc, char *argv[]) {
    Application app(argc, argv);
    return app.exec();
}
