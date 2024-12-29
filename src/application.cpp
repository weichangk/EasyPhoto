#include "inc/application.h"
#include "mainpresenter.h"
#include "mainview.h"
#include "core/theme.h"
#include "core/font.h"

#include <Magick++.h>

using namespace Magick;
using namespace qtmaterialcore;

Application::Application(int argc, char *argv[]) :
    QApplication(argc, argv) {
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

    MainView mainView;
    MainPresenter mainPresenter(&mainView);
    mainView.show();

    return app.exec();
}
