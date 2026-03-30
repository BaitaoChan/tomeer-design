#include "CukeScopePrivate.h"
#include "CukeScope.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeScopePrivate::CukeScopePrivate(CukeScope *q)
    : q_ptr(q) {
}

CukeScopePrivate::~CukeScopePrivate() = default;

CUKE_NAMESPACE_END(pub)