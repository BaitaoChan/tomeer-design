#include "CukeToolTipPrivate.h"
#include "CukeToolTip.h"

CUKE_NAMESPACE_BEGIN()
ToolTip *ToolTipPrivate::_toolTip = nullptr;
ToolTipPrivate::ToolTipPrivate(ToolTip *q)
    : QObject(q),
      q_ptr(q) {
}

ToolTipPrivate::~ToolTipPrivate() = default;

CUKE_NAMESPACE_END