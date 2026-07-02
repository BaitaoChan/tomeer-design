#include "CukeMenu.h"
#include "CukeMenuStyle.h"
#include "CukeMenuPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeMenu, CukeThemeType::ThemeMode, ThemeMode)
CukeMenu::CukeMenu(QWidget *parent)
    : QMenu(parent),
      d_ptr(new CukeMenuPrivate(this)) {
    Q_D(CukeMenu);
    // 确保应用基本样式
    ensurePolished();
    setStyle(new CukeMenuStyle(style()));
    connect(cTheme, &CukeTheme::themeModeChanged, this, &CukeMenu::onThemeChanged);
}

CukeMenu::CukeMenu(const QString &title, QWidget *parent)
    : CukeMenu(parent) {
    setTitle(title);
}

void CukeMenu::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeMenu);
    setThemeMode(mode);
    update();
}

CukeMenu::~CukeMenu() = default;
CUKE_NAMESPACE_END(pub)