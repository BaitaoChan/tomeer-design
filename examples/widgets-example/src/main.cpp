#include <QApplication>

#include "main.h"
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TOMEER_APP->init();

    MainWindow w;
    TOMEER_THEME->setThemeMode(ThemeType::System);
    w.show();

    return app.exec();
}
