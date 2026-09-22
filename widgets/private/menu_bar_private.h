#ifndef MENU_BAR_PRIVATE_H
#define MENU_BAR_PRIVATE_H
#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class MenuBar;
class MenuBarPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(MenuBar)
public:
    explicit MenuBarPrivate(MenuBar *q);
    ~MenuBarPrivate() override;
};
TOMEER_NAMESPACE_END

#endif // MENU_BAR_PRIVATE_H
