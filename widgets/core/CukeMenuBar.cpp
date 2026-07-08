#include "CukeMenuBar.h"
#include "CukeMenuBarStyle.h"
#include "CukeMenuBarPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(MenuBar, ThemeType::ThemeMode, ThemeMode)
MenuBar::MenuBar(QWidget *parent)
    : QMenuBar(parent),
      d_ptr(new MenuBarPrivate(this)) {
    Q_D(MenuBar);
    setStyle(new MenuBarStyle(style()));
    setFixedHeight(24);
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &MenuBar::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

MenuBar::~MenuBar() = default;

void MenuBar::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(MenuBar);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)