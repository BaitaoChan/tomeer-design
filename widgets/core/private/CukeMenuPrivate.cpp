#include "CukeMenuPrivate.h"
#include "CukeMenu.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeMenuPrivate::CukeMenuPrivate(CukeMenu *q)
    : QObject(q),
      q_ptr(q) {
}

CukeMenuPrivate::~CukeMenuPrivate() = default;

CUKE_NAMESPACE_END(pub)