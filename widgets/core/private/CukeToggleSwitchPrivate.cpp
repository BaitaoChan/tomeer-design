#include "CukeToggleSwitchPrivate.h"
#include "CukeToggleSwitch.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeToggleSwitchPrivate::CukeToggleSwitchPrivate(CukeToggleSwitch *q)
    : QObject(q),
      q_ptr(q) {
}

CukeToggleSwitchPrivate::~CukeToggleSwitchPrivate() = default;

CUKE_NAMESPACE_END(pub)