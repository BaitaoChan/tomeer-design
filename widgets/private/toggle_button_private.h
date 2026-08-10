#ifndef TOGGLE_BUTTON_PRIVATE_H
#define TOGGLE_BUTTON_PRIVATE_H
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class ToggleButton;
class ToggleButtonPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(ToggleButton)
public:
    explicit ToggleButtonPrivate(ToggleButton *q);
    ~ToggleButtonPrivate() override;

};
TOMEER_NAMESPACE_END

#endif // TOGGLE_BUTTON_PRIVATE_H