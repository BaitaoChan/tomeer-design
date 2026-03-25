#include "CukeHubPrivate.h"
#include "CukeHub.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeHubPrivate::CukeHubPrivate(CukeHub *q)
    : q_ptr(q) {
}

CukeHubPrivate::~CukeHubPrivate() = default;

CUKE_NAMESPACE_END(pub)