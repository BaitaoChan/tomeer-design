#include "CukeLineEditStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeLineEditStyle::CukeLineEditStyle(QStyle *style)
    : QProxyStyle(style),
      CukeScope(this) {
}

CukeLineEditStyle::~CukeLineEditStyle() = default;

CUKE_NAMESPACE_END(pub)
