#include "CukeWindowPrivate.h"
#include "CukeWindow.h"

CUKE_NAMESPACE_BEGIN()
CUKE_Q_PROPERTY_IMPL(WindowPrivate, bool, IsResize)
CUKE_Q_PROPERTY_IMPL(WindowPrivate, bool, IsDrag)
CUKE_Q_PROPERTY_IMPL(WindowPrivate, bool, IsApplied)
WindowPrivate::WindowPrivate(Window *q)
    : QObject(q),
      q_ptr(q) {
}

WindowPrivate::~WindowPrivate() = default;

CUKE_NAMESPACE_END