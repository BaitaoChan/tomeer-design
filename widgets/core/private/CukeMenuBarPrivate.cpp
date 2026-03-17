#include "CukeMenuBarPrivate.h"
#include "CukeMenuBar.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeMenuBarPrivate::CukeMenuBarPrivate(CukeMenuBar *q)
    : QObject(q),
      q_ptr(q) {
}

CukeMenuBarPrivate::~CukeMenuBarPrivate() = default;

CUKE_NAMESPACE_END(widget)