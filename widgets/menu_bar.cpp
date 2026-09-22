#include "menu_bar.h"
#include "menu_bar_style.h"
#include "menu_bar_private.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(MenuBar, ThemeType::ThemeMode, ThemeMode)
MenuBar::MenuBar(QWidget *parent)
    : QMenuBar(parent),
      d_ptr(new MenuBarPrivate(this)) {
    Q_D(MenuBar);
    setStyle(new MenuBarStyle(style()));
    setFixedHeight(24);
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &MenuBar::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

MenuBar::~MenuBar() = default;

void MenuBar::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(MenuBar);
    setThemeMode(mode);
    update();
}

TOMEER_NAMESPACE_END
