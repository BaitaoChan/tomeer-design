#include "push_button_private.h"

#include "push_button.h"

TOMEER_NAMESPACE_BEGIN()
PushButtonPrivate::PushButtonPrivate(PushButton *q)
    : QObject(q),
      q_ptr(q) {
}

PushButtonPrivate::~PushButtonPrivate() = default;
TOMEER_NAMESPACE_END
