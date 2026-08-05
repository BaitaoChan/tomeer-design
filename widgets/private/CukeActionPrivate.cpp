#include "CukeIcon.h"
#include "CukeActionPrivate.h"
#include "CukeAction.h"

CUKE_NAMESPACE_BEGIN()
ActionPrivate::ActionPrivate(Action *q)
    : QObject(q),
      q_ptr(q) {
}

ActionPrivate::~ActionPrivate() = default;

CUKE_NAMESPACE_END