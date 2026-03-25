#include "CukeContextPrivate.h"
#include "CukeHub.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeContextPrivate::CukeContextPrivate(CukeHub *q)
    : q_ptr(q) {
}

CukeContextPrivate::~CukeContextPrivate() = default;

CUKE_NAMESPACE_END(pub)