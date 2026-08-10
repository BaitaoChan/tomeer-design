#ifndef MENU_H
#define MENU_H
#include <QMenu>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class Action;
class MenuPrivate;
class WIDGETS_EXPORT Menu : public QMenu {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(Menu)
    TOMEER_Q_PROPERTY_DECL(IconType::Icon, Icon)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    using QMenu::addMenu;
    using QMenu::setIcon;

    explicit Menu(QWidget* parent = nullptr);
    explicit Menu(const QString &title, QWidget *parent = nullptr);
    ~Menu() override;

    Action *addMenu(Menu *menu);

protected:
    void showEvent(QShowEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};

TOMEER_NAMESPACE_END

#endif // MENU_H