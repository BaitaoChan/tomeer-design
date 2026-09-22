#include "action.h"
#include "menu.h"
#include "menu_style.h"
#include "menu_private.h"

#include "icon.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(Menu, ThemeType::ThemeMode, ThemeMode)
Menu::Menu(QWidget *parent)
    : QMenu(parent),
      d_ptr(new MenuPrivate(this)) {
    Q_D(Menu);
    // 确保应用基本样式
    ensurePolished();
    setStyle(new MenuStyle(style()));
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &Menu::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

Menu::Menu(const QString &title, QWidget *parent)
    : Menu(parent) {
    setTitle(title);
}

void Menu::setIcon(IconType::Icon pIcon) {
    if (_pIcon != pIcon) {
        _pIcon = pIcon;
        pIconChanged();
        setIcon(TOMEER_ICON->getIcon(_pIcon));
    }
}

IconType::Icon Menu::getIcon() const {
    return _pIcon;
}

Action *Menu::addMenu(Menu *menu) {
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
TOMEER_NAMESPACE_END
