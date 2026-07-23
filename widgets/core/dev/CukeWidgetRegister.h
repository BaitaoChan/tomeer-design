#ifndef CUKEWIDGETREGISTER_H
#define CUKEWIDGETREGISTER_H
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class WidgetRegisterPrivate;
class CUKE_EXPORT WidgetRegister {
    CUKE_DECLARE_DPTR(WidgetRegister);
public:
    explicit WidgetRegister(QObject *child);
    virtual ~WidgetRegister();

    void add(int key, void *child) const;
    void *object(int key) const;
    QList<void *> objects() const;
    bool contains(int key) const;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEWIDGETREGISTER_H