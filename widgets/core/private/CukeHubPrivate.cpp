#include "CukeHubPrivate.h"
#include "CukeScope.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeHubPrivate::CukeHubPrivate(CukeScope *q)
    : q_ptr(q) {
}

CukeHubPrivate::~CukeHubPrivate() = default;

CUKE_NAMESPACE_END(pub)