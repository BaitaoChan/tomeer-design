#include "CukeToolBarPrivate.h"
#include "CukeToolBar.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeToolBarPrivate::CukeToolBarPrivate(CukeToolBar *q)
    : QObject(q),
      q_ptr(q) {
}

CukeToolBarPrivate::~CukeToolBarPrivate() = default;
CUKE_NAMESPACE_END(pub)