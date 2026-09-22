#ifndef WIDGET_REGISTER_PRIVATE_H
#define WIDGET_REGISTER_PRIVATE_H
#include <QHash>

#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class WidgetRegister;
class WidgetRegisterPrivate {
    TOMEER_DECLARE_QPTR(WidgetRegister)
public:
    explicit WidgetRegisterPrivate(WidgetRegister *q);
    ~WidgetRegisterPrivate();

private:
    QObject *_child = nullptr;

    QHash<int, void *> _children;
};
TOMEER_NAMESPACE_END

#endif // WIDGET_REGISTER_PRIVATE_H
