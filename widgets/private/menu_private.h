#ifndef MENU_PRIVATE_H
#define MENU_PRIVATE_H
#include "menu.h"
#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class Menu;
class MenuPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(Menu)
public:
    explicit MenuPrivate(Menu *q);
    ~MenuPrivate() override;

};
TOMEER_NAMESPACE_END

#endif // MENU_PRIVATE_H