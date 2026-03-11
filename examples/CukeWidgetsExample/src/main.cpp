#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.show();
    pTheme->setThemeMode(CukeThemeType::Light);

    return app.exec();
}