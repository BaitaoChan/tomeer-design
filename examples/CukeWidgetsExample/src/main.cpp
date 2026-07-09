#include <QApplication>

#include "CukeApplication.h"
#include "MainWindow.h"

using namespace cuke::pub;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CUKE_APP->init();

    MainWindow w;
    w.show();
    CUKE_THEME->setThemeMode(ThemeType::System);

    return app.exec();
}