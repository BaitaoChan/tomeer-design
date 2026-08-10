#ifndef MENU_BAR_H
#define MENU_BAR_H
#include <QMenuBar>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class MenuBarPrivate;
class WIDGETS_EXPORT MenuBar : public QMenuBar {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(MenuBar)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit MenuBar(QWidget* parent = nullptr);
    ~MenuBar() override;

protected:
    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // MENU_BAR_H