#include "inc/application.h"
#include "mainpresenter.h"
#include "mainview.h"

#include <Magick++.h>

using namespace Magick;

Application::Application(int argc, char *argv[]) :
    QApplication(argc, argv) {
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
