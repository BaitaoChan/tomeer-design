#include "navigation_bar_style.h"

TOMEER_NAMESPACE_BEGIN()

NavigationBarStyle::NavigationBarStyle(QStyle *style)
    : QProxyStyle(style) {
}

NavigationBarStyle::~NavigationBarStyle() = default;

void NavigationBarStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

int NavigationBarStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

TOMEER_NAMESPACE_END