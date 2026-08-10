#ifndef WIDGET_REGISTER_H
#define WIDGET_REGISTER_H
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class WidgetRegisterPrivate;
class WIDGETS_EXPORT WidgetRegister {
    TOMEER_DECLARE_DPTR(WidgetRegister);
public:
    explicit WidgetRegister(QObject *child);
    virtual ~WidgetRegister();

    void add(int key, void *child) const;
    void *object(int key) const;
    QList<void *> objects() const;
    bool contains(int key) const;
};
TOMEER_NAMESPACE_END

#endif // WIDGET_REGISTER_H