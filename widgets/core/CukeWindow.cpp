#include <QPainter>

#include "CukeWindow.h"
#include "CukeWindowStyle.h"
#include "CukeWindowPrivate.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeWindow::CukeWindow(QWidget *parent)
    : CukeContextMixin(parent),
      d_ptr(new CukeWindowPrivate(this)) {
    // setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    resize(1280, 720);
    setStyle(new CukeWindowStyle(style()));
    setStyleSheet("QMainWindow { background: transparent; }");
}

CukeWindow::~CukeWindow() = default;

void CukeWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), pThemeColor(_themeMode, WindowAlpha));

    QMainWindow::paintEvent(event);
}

CUKE_NAMESPACE_END(widget)