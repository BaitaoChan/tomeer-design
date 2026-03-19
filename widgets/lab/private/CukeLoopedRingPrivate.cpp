#include "CukeLoopedRingPrivate.h"
#include "CukeLoopedRing.h"

CUKE_NAMESPACE_BEGIN(lab)
CukeLoopedRingPrivate::CukeLoopedRingPrivate(CukeLoopedRing *q)
    : QObject(q),
      q_ptr(q) {
}

CukeLoopedRingPrivate::~CukeLoopedRingPrivate() = default;

CUKE_NAMESPACE_END(lab)
