#include "CukeToolBarStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeToolBarStyle::CukeToolBarStyle(QStyle *style)
    : QProxyStyle(style),
      CukeHub(this) {
}

CukeToolBarStyle::~CukeToolBarStyle() = default;

CUKE_NAMESPACE_END(pub)