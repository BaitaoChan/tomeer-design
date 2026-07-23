#include "CukeLineEditStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
LineEditStyle::LineEditStyle(QStyle *style)
    : QProxyStyle(style) {
}

LineEditStyle::~LineEditStyle() = default;

CUKE_NAMESPACE_END(pub)