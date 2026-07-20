#include "CukeScrollAreaStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
ScrollAreaStyle::ScrollAreaStyle(QStyle *style)
    : QProxyStyle(style) {
}

ScrollAreaStyle::~ScrollAreaStyle() = default;

CUKE_NAMESPACE_END(pub)