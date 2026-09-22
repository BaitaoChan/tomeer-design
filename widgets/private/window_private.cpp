#include "window_private.h"
#include "window.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(WindowPrivate, bool, IsResize)
TOMEER_Q_PROPERTY_IMPL(WindowPrivate, bool, IsDrag)
TOMEER_Q_PROPERTY_IMPL(WindowPrivate, bool, IsApplied)
WindowPrivate::WindowPrivate(Window *q)
    : QObject(q),
      q_ptr(q) {
}

WindowPrivate::~WindowPrivate() = default;

TOMEER_NAMESPACE_END
