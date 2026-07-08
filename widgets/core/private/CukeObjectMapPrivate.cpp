#include "CukeObjectMapPrivate.h"
#include "CukeObjectMap.h"

CUKE_NAMESPACE_BEGIN(pub)
ObjectMapPrivate::ObjectMapPrivate(ObjectMap *q)
    : q_ptr(q) {
}

ObjectMapPrivate::~ObjectMapPrivate() = default;

CUKE_NAMESPACE_END(pub)