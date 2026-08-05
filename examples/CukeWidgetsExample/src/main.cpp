#include <QApplication>

#include "CukeApplication.h"
#include "MainWindow.h"

using namespace cuke;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CUKE_APP->init();

    MainWindow w;
    CUKE_THEME->setThemeMode(ThemeType::System);
    w.show();

    return app.exec();
}