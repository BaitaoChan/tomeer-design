#include "CukeMenuBar.h"
#include "CukeMenuBarStyle.h"
#include "CukeMenuBarPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeMenuBar, CukeThemeType::ThemeMode, ThemeMode)
CukeMenuBar::CukeMenuBar(QWidget *parent)
    : QMenuBar(parent),
      d_ptr(new CukeMenuBarPrivate(this)) {
    Q_D(CukeMenuBar);
    setStyle(new CukeMenuBarStyle(style()));
    setFixedHeight(24);
    connect(CUKE_THEME, &CukeTheme::themeModeChanged, this, &CukeMenuBar::onThemeChanged);
}

CukeMenuBar::~CukeMenuBar() = default;

void CukeMenuBar::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeMenuBar);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)