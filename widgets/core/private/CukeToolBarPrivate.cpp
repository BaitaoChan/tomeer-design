#include "CukeToolBarPrivate.h"
#include "CukeToolBar.h"

CUKE_NAMESPACE_BEGIN(pub)
ToolBarPrivate::ToolBarPrivate(ToolBar *q)
    : QObject(q),
      q_ptr(q) {
}

ToolBarPrivate::~ToolBarPrivate() = default;
CUKE_NAMESPACE_END(pub)