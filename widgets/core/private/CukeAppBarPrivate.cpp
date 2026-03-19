#include "CukeAppBarPrivate.h"
#include "CukeAppBar.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeAppBarPrivate::CukeAppBarPrivate(CukeAppBar *q)
    : QObject(q),
      q_ptr(q) {
}

CukeAppBarPrivate::~CukeAppBarPrivate() = default;

CUKE_NAMESPACE_END(pub)