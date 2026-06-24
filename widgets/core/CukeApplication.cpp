#include <QFontDatabase>
#include <QApplication>

#include "CukeApplication.h"

CUKE_NAMESPACE_BEGIN(pub)
    CUKE_Q_SINGLETON_IMPL(CukeApplication)
CukeApplication::CukeApplication(QObject *parent)
    : QObject(parent) {
}

CukeApplication::~CukeApplication() = default;

void CukeApplication::init() {
    QFontDatabase::addApplicationFont(":/CukeGlyphs.ttf");

    QFont font("Microsoft YaHei");
    font.setPixelSize(13);
    font.setStyleStrategy(QFont::PreferAntialias);
    font.setHintingPreference(QFont::PreferFullHinting);
    QApplication::setFont(font);
}

CUKE_NAMESPACE_END(pub)