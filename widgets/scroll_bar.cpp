#include "scroll_bar.h"
#include "scroll_bar_private.h"
#include "scroll_bar_style.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(ScrollBar, ThemeType::ThemeMode, ThemeMode)
ScrollBar::ScrollBar(QWidget *parent)
    : QScrollBar(parent),
      d_ptr(new ScrollBarPrivate(this)) {
    setStyle(new ScrollBarStyle(style()));
    setAttribute(Qt::WA_Hover);

    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &ScrollBar::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
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

TOMEER_NAMESPACE_END