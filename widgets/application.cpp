#include <QFontDatabase>
#include <QApplication>

#include "application.h"

TOMEER_NAMESPACE_BEGIN()
    TOMEER_Q_SINGLETON_IMPL(Application)
Application::Application(QObject *parent)
    : QObject(parent) {
}

Application::~Application() = default;

void Application::init() {
    QFontDatabase::addApplicationFont(":/tomeer.ttf");

    QFont font("Microsoft YaHei");
    font.setPixelSize(13);
    font.setStyleStrategy(QFont::PreferAntialias);
    font.setHintingPreference(QFont::PreferFullHinting);
    QApplication::setFont(font);
}

TOMEER_NAMESPACE_END
