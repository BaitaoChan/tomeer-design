#include "tool_bar_private.h"
#include "tool_bar.h"

TOMEER_NAMESPACE_BEGIN()
ToolBarPrivate::ToolBarPrivate(ToolBar *q)
    : QObject(q),
      q_ptr(q) {
}

ToolBarPrivate::~ToolBarPrivate() = default;
TOMEER_NAMESPACE_END
