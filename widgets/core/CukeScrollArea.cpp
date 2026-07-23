#include <QPainter>

#include "CukeScrollArea.h"
#include "CukeScrollAreaPrivate.h"
#include "CukeScrollBar.h"

CUKE_NAMESPACE_BEGIN(pub)
    CUKE_Q_PROPERTY_IMPL(ScrollArea, ThemeType::ThemeMode, ThemeMode)
ScrollArea::ScrollArea(QWidget *parent)
    : QScrollArea(parent),
      d_ptr(new ScrollAreaPrivate(this)) {
    setHorizontalScrollBar(new ScrollBar(this));
    setVerticalScrollBar(new ScrollBar(this));
    setStyleSheet("QScrollArea { border: none; background: transparent; }");
    viewport()->setStyleSheet("background: transparent;");

    connect(CUKE_THEME, &Theme::themeModeChanged, this, QOverload<>::of(&QWidget::update));
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

ScrollArea::~ScrollArea() = default;

void ScrollArea::paintEvent(QPaintEvent *event) {
    QScrollArea::paintEvent(event);
}

void ScrollArea::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(ScrollArea);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)