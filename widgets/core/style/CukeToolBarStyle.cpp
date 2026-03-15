#include "CukeToolBarStyle.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeToolBarStyle::CukeToolBarStyle(QStyle *style)
    : CukeContextMixin(style) {
}

CukeToolBarStyle::~CukeToolBarStyle() = default;

CUKE_NAMESPACE_END(widget)