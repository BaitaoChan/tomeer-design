#include "CukeContextPrivate.h"
#include "CukeContext.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeContextPrivate::CukeContextPrivate(CukeContext *q)
    : q_ptr(q) {
}

CukeContextPrivate::~CukeContextPrivate() = default;

CUKE_NAMESPACE_END(pub)