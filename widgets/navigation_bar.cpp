#include "navigation_bar.h"
#include "navigation_bar_private.h"
#include "navigation_bar_style.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(NavigationBar, ThemeType::ThemeMode, ThemeMode)
NavigationBar::NavigationBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new NavigationBarPrivate(this)) {
    Q_D(NavigationBar);
}

NavigationBar::~NavigationBar() = default;

void NavigationBar::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(NavigationBar);
    setThemeMode(mode);
    update();
}
TOMEER_NAMESPACE_END