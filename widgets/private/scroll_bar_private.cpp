#include "scroll_bar_private.h"
#include "scroll_bar.h"

TOMEER_NAMESPACE_BEGIN()
ScrollBarPrivate::ScrollBarPrivate(ScrollBar *q)
    : QObject(q),
      q_ptr(q) {
}

ScrollBarPrivate::~ScrollBarPrivate() = default;

TOMEER_NAMESPACE_END