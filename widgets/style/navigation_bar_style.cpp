#include "navigation_bar_style.h"

TOMEER_NAMESPACE_BEGIN()

NavigationBarStyle::NavigationBarStyle(QStyle *style)
    : QProxyStyle(style) {
}

NavigationBarStyle::~NavigationBarStyle() = default;
TOMEER_NAMESPACE_END