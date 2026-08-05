#include "CukeScrollBarPrivate.h"
#include "CukeScrollBar.h"

CUKE_NAMESPACE_BEGIN()
ScrollBarPrivate::ScrollBarPrivate(ScrollBar *q)
    : QObject(q),
      q_ptr(q) {
}

ScrollBarPrivate::~ScrollBarPrivate() = default;

CUKE_NAMESPACE_END