#include "LineEditStyle.h"

CUKE_BEGIN_NAMESPACE(widget)
LineEditStyle::LineEditStyle(QStyle *style)
    : ContextMixin(style) {
}

LineEditStyle::~LineEditStyle() = default;

CUKE_END_NAMESPACE(widget)
