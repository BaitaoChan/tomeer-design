#include "CukeWindowPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
CukeWindowPrivate::CukeWindowPrivate(CukeWindow *q)
    : q_ptr(q) {
}

CukeWindowPrivate::~CukeWindowPrivate() = default;

CUKE_END_NAMESPACE(widget)