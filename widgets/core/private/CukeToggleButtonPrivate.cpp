#include "CukeToggleButtonPrivate.h"
#include "CukeToggleButton.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeToggleButtonPrivate::CukeToggleButtonPrivate(CukeToggleButton *q)
    : QObject(q),
      q_ptr(q) {
}

CukeToggleButtonPrivate::~CukeToggleButtonPrivate() = default;

CUKE_NAMESPACE_END(widget)