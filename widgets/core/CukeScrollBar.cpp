#include "CukeScrollBar.h"
#include "CukeScrollBarPrivate.h"
#include "CukeScrollBarStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(ScrollBar, ThemeType::ThemeMode, ThemeMode)
ScrollBar::ScrollBar(QWidget *parent)
    : QScrollBar(parent),
      d_ptr(new ScrollBarPrivate(this)) {
    setStyle(new ScrollBarStyle(style()));

    connect(CUKE_THEME, &Theme::themeModeChanged, this, &ScrollBar::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

ScrollBar::ScrollBar(Qt::Orientation orientation, QWidget *parent)
    : ScrollBar(parent) {
    setOrientation(orientation);
}

ScrollBar::~ScrollBar() = default;

void ScrollBar::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(ScrollBar);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)