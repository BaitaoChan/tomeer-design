#include "WindowPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
WindowPrivate::WindowPrivate(Window *q)
    : q_ptr(q) {
}

WindowPrivate::~WindowPrivate() = default;

CUKE_END_NAMESPACE(widget)