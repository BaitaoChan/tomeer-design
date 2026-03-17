#include <QApplication>

#include "CukeApplication.h"
#include "MainWindow.h"

using namespace cuke::widget;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    cApp->init();

    MainWindow w;
    w.show();
    cTheme->setThemeMode(CukeThemeType::Light);

    return app.exec();
}