#include "CukeToolBar.h"
#include "CukeToolBarStyle.h"
#include "CukeToolBarPrivate.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeToolBar, CukeThemeType::ThemeMode, ThemeMode)
CukeToolBar::CukeToolBar(QWidget *parent)
    : QToolBar(parent) {
    setStyle(new CukeToolBarStyle());
    connect(cTheme, &CukeTheme::themeModeChanged, this, &CukeToolBar::onThemeChanged);
}

CukeToolBar::~CukeToolBar() = default;

void CukeToolBar::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeToolBar);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)