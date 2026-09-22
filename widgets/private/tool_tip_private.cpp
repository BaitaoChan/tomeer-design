#include "tool_tip_private.h"
#include "tool_tip.h"

TOMEER_NAMESPACE_BEGIN()
ToolTip *ToolTipPrivate::_toolTip = nullptr;
ToolTipPrivate::ToolTipPrivate(ToolTip *q)
    : QObject(q),
      q_ptr(q) {
}

ToolTipPrivate::~ToolTipPrivate() = default;

TOMEER_NAMESPACE_END
