#ifndef PUSH_BUTTON_PRIVATE_H
#define PUSH_BUTTON_PRIVATE_H
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class PushButton;
class PushButtonPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(PushButton)
public:
    explicit PushButtonPrivate(PushButton *q);
    ~PushButtonPrivate() override;
};
TOMEER_NAMESPACE_END

#endif // PUSH_BUTTON_PRIVATE_H
