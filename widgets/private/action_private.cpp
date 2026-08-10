#include "icon.h"
#include "action_private.h"
#include "action.h"

TOMEER_NAMESPACE_BEGIN()
ActionPrivate::ActionPrivate(Action *q)
    : QObject(q),
      q_ptr(q) {
}

ActionPrivate::~ActionPrivate() = default;

TOMEER_NAMESPACE_END