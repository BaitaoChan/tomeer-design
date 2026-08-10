#include "toggle_button_private.h"

#include "toggle_button.h"

TOMEER_NAMESPACE_BEGIN()
ToggleButtonPrivate::ToggleButtonPrivate(ToggleButton *q)
    : QObject(q),
      q_ptr(q) {
}

ToggleButtonPrivate::~ToggleButtonPrivate() = default;
TOMEER_NAMESPACE_END