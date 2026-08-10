#include <QApplication>

#include "application.h"
#include "MainWindow.h"

using namespace tomeer;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TOMEER_APP->init();

    MainWindow w;
    TOMEER_THEME->setThemeMode(ThemeType::System);
    w.show();

    return app.exec();
}