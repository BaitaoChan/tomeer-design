#include "navigation_bar_view_style.h"

TOMEER_NAMESPACE_BEGIN()

NavigationBarViewStyle::NavigationBarViewStyle(QStyle *style)
    : QProxyStyle(style) {
}

NavigationBarViewStyle::~NavigationBarViewStyle() = default;

void NavigationBarViewStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void NavigationBarViewStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawControl(element, option, painter, widget);
}

int NavigationBarViewStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

QSize NavigationBarViewStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const {
    return QProxyStyle::sizeFromContents(type, option, size, widget);
}

TOMEER_NAMESPACE_END