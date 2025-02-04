#include "application.h"
#include "settings.h"
#include "mainrepository.h"
#include "mainpresenter.h"
#include "mainview.h"
#include "core/theme.h"
#include "core/font.h"

#include <Magick++.h>

using namespace Magick;
using namespace qtmaterialcore;

Application::Application(int argc, char *argv[]) :
    QApplication(argc, argv) {
    setOrganizationName(APPLICATION_ORGANIZATION_NAME);
    setOrganizationDomain(APPLICATION_ORGANIZATION_DOMAIN);
    setApplicationName(APPLICATION_ID);
    setApplicationDisplayName(APPLICATION_DISPLAY_NAME);
    SETTINGS->load();
    qtmaterialcore::Theme::setTheme(qtmaterialcore::Theme::DARK);
    qtmaterialcore::Font::setFont(qtmaterialcore::Font::ROBOTO_REGULAR);
    qtmaterialcore::Font::setIconFont(":/font/iconfont.ttf");
    InitializeMagick(*argv);
#if QT_VERSION < 0x060000
    setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif
}

int main(int argc, char *argv[]) {
    Application app(argc, argv);

    MainRepository mainRepository;
    MainView mainView;
    MainPresenter mainPresenter(&mainView, &mainRepository);
    mainView.show();

    return app.exec();
}
