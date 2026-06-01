#include "CukeObjectMapPrivate.h"
#include "CukeObjectMap.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeObjectMapPrivate::CukeObjectMapPrivate(CukeObjectMap *q)
    : q_ptr(q) {
}

CukeObjectMapPrivate::~CukeObjectMapPrivate() = default;

CUKE_NAMESPACE_END(pub)