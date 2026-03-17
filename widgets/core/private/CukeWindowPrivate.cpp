#include "CukeWindowPrivate.h"
#include "CukeWindow.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeWindowPrivate::CukeWindowPrivate(CukeWindow *q)
    : QObject(q),
      q_ptr(q) {
}

CukeWindowPrivate::~CukeWindowPrivate() = default;

CUKE_NAMESPACE_END(widget)