#include "CukeToggleButtonPrivate.h"
#include "CukeToggleButton.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeToggleButtonPrivate::CukeToggleButtonPrivate(CukeToggleButton *q)
    : QObject(q),
      q_ptr(q) {
}

CukeToggleButtonPrivate::~CukeToggleButtonPrivate() = default;

CUKE_NAMESPACE_END(pub)