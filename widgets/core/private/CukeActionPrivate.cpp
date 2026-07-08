#include "CukeActionPrivate.h"

#include "CukeAction.h"

CUKE_NAMESPACE_BEGIN(pub)
ActionPrivate::ActionPrivate(Action *q)
    : QObject(q),
      q_ptr(q) {
}

ActionPrivate::~ActionPrivate() = default;

CUKE_NAMESPACE_END(pub)
