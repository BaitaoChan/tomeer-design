#ifndef MESSAGE_BAR_PRIVATE_H
#define MESSAGE_BAR_PRIVATE_H
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class MessageBar;
class MessageBarPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(MessageBar)
public:
    explicit MessageBarPrivate(MessageBar *q);
    ~MessageBarPrivate() override;
};
TOMEER_NAMESPACE_END

#endif // MESSAGE_BAR_PRIVATE_H
