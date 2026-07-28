#include "CukeAction.h"
#include "CukeMenu.h"
#include "CukeMenuStyle.h"
#include "CukeMenuPrivate.h"

#include "CukeIcon.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(Menu, ThemeType::ThemeMode, ThemeMode)
Menu::Menu(QWidget *parent)
    : QMenu(parent),
      d_ptr(new MenuPrivate(this)) {
    Q_D(Menu);
    // 确保应用基本样式
    ensurePolished();
    setStyle(new MenuStyle(style()));
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &Menu::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

Menu::Menu(const QString &title, QWidget *parent)
    : Menu(parent) {
    setTitle(title);
}

void Menu::setCukeIcon(IconType::Icon pCukeIcon) {
    if (_pCukeIcon != pCukeIcon) {
        _pCukeIcon = pCukeIcon;
        pCukeIconChanged();
        setIcon(CUKE_ICON->getCukeIcon(_pCukeIcon));
    }
}

IconType::Icon Menu::getCukeIcon() const {
    return _pCukeIcon;
}

Action *Menu::addCukeMenu(Menu *menu) {
    if (!menu)
        return nullptr;
    if (!menu->parent())
        menu->setParent(this);
    const auto action = new Action(menu->icon(), menu->title(), this);
    action->setMenu(menu);
    addAction(action);

    return action;
}

void Menu::showEvent(QShowEvent *event) {
    Q_D(Menu);
    QMenu::showEvent(event);
    move(pos().x() - 6, pos().y());
}

void Menu::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(Menu);
    setThemeMode(mode);
    update();
}

Menu::~Menu() = default;
CUKE_NAMESPACE_END(pub)