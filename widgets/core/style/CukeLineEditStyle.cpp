#include "CukeLineEditStyle.h"

CUKE_BEGIN_NAMESPACE(widget)
CukeLineEditStyle::CukeLineEditStyle(QStyle *style)
    : CukeContextMixin(style) {
}

CukeLineEditStyle::~CukeLineEditStyle() = default;

CUKE_END_NAMESPACE(widget)
