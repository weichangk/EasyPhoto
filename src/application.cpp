#include "inc/application.h"
#include <Magick++.h>
using namespace Magick;

Application::Application(int argc, char *argv[]) :
    QApplication(argc, argv) {
    initUi();
    InitializeMagick(*argv);
}

void Application::initUi() {
#if QT_VERSION < 0x060000
    setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif
}

int main(int argc, char *argv[]) {
    Application app(argc, argv);
    return app.exec();
}
