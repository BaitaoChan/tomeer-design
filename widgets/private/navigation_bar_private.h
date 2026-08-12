#ifndef NAVIGATION_BAR_PRIVATE_H
#define NAVIGATION_BAR_PRIVATE_H
#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class NavigationBar;
class NavigationBarPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(NavigationBar)
public:
    explicit NavigationBarPrivate(NavigationBar *q);
    ~NavigationBarPrivate() override;
};
TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_PRIVATE_H