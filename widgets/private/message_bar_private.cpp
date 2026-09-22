#include "message_bar_private.h"

#include "message_bar.h"

TOMEER_NAMESPACE_BEGIN()
MessageBarPrivate::MessageBarPrivate(MessageBar *q)
    : QObject(q),
      q_ptr(q) {
}

MessageBarPrivate::~MessageBarPrivate() = default;

TOMEER_NAMESPACE_END
