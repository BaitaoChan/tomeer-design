#include "CukeScrollAreaPrivate.h"
#include "CukeScrollArea.h"

CUKE_NAMESPACE_BEGIN()
ScrollAreaPrivate::ScrollAreaPrivate(ScrollArea *q)
    : QObject(q),
      q_ptr(q) {
}

ScrollAreaPrivate::~ScrollAreaPrivate() = default;

CUKE_NAMESPACE_END