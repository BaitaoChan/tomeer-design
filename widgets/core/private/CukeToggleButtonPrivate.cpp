#include "CukeToggleButtonPrivate.h"
#include "CukeToggleButton.h"

CUKE_NAMESPACE_BEGIN(pub)
ToggleButtonPrivate::ToggleButtonPrivate(ToggleButton *q)
    : QObject(q),
      q_ptr(q) {
}

ToggleButtonPrivate::~ToggleButtonPrivate() = default;

CUKE_NAMESPACE_END(pub)