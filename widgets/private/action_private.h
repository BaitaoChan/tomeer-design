#ifndef ACTION_PRIVATE_H
#define ACTION_PRIVATE_H

#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class Action;
class ActionPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(Action)
public:
    explicit ActionPrivate(Action *q);
    ~ActionPrivate() override;
};
TOMEER_NAMESPACE_END

#endif // ACTION_PRIVATE_H
