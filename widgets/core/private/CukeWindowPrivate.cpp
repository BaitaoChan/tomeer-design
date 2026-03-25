#include "CukeWindowPrivate.h"
#include "CukeWindow.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeWindowPrivate, bool, IsResize)
CUKE_Q_PROPERTY_IMPL(CukeWindowPrivate, bool, IsDrag)
CukeWindowPrivate::CukeWindowPrivate(CukeWindow *q)
    : QObject(q),
      q_ptr(q) {
}

CukeWindowPrivate::~CukeWindowPrivate() = default;

CUKE_NAMESPACE_END(pub)