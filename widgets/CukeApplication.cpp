#include <QFontDatabase>
#include <QApplication>

#include "CukeApplication.h"

CUKE_NAMESPACE_BEGIN()
    CUKE_Q_SINGLETON_IMPL(Application)
Application::Application(QObject *parent)
    : QObject(parent) {
}

Application::~Application() = default;

void Application::init() {
    QFontDatabase::addApplicationFont(":/CukeGlyphs.ttf");

    QFont font("Microsoft YaHei");
    font.setPixelSize(13);
    font.setStyleStrategy(QFont::PreferAntialias);
    font.setHintingPreference(QFont::PreferFullHinting);
    QApplication::setFont(font);
}

CUKE_NAMESPACE_END