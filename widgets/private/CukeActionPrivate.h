#ifndef CUKEACTIONPRIVATE_H
#define CUKEACTIONPRIVATE_H

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN()
class Action;
class ActionPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(Action)
public:
    explicit ActionPrivate(Action *q);
    ~ActionPrivate() override;
};
CUKE_NAMESPACE_END

#endif // CUKEACTIONPRIVATE_H