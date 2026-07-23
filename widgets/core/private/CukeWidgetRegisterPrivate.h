#ifndef CUKEWIDGETREGISTERPRIVATE_H
#define CUKEWIDGETREGISTERPRIVATE_H
#include <QHash>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class WidgetRegister;
class WidgetRegisterPrivate {
    CUKE_DECLARE_QPTR(WidgetRegister)
public:
    explicit WidgetRegisterPrivate(WidgetRegister *q);
    ~WidgetRegisterPrivate();

private:
    QObject *_child = nullptr;

    QHash<int, void *> _children;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEWIDGETREGISTERPRIVATE_H