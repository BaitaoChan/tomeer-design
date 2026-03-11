#include <QPainter>

#include "CukeWindow.h"
#include "CukeWindowStyle.h"
#include "CukeWindowPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
CukeWindow::CukeWindow(QWidget *parent)
    : CukeContextMixin(parent),
      d_ptr(new CukeWindowPrivate(this)) {
    resize(1280, 720);
    setStyle(new CukeWindowStyle(style()));
    setStyleSheet("QMainWindow { background: transparent; }");
}

CukeWindow::~CukeWindow() = default;

void CukeWindow::onThemeChanged(CukeThemeType::ThemeMode mode) {
    CukeContextMixin::onThemeChanged(mode);
    update();
}

void CukeWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), pThemeColor(_themeMode, Window));

    QMainWindow::paintEvent(event);
}

CUKE_END_NAMESPACE(widget)