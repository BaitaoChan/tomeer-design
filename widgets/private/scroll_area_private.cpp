#include "scroll_area_private.h"
#include "scroll_area.h"

TOMEER_NAMESPACE_BEGIN()
ScrollAreaPrivate::ScrollAreaPrivate(ScrollArea *q)
    : QObject(q),
      q_ptr(q) {
}

ScrollAreaPrivate::~ScrollAreaPrivate() = default;

TOMEER_NAMESPACE_END