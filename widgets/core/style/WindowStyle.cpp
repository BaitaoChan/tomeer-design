#include "WindowStyle.h"

CUKE_BEGIN_NAMESPACE(widget)
WindowStyle::WindowStyle(QStyle *style)
    : ContextMixin(style) {
}

WindowStyle::~WindowStyle() = default;

void WindowStyle::drawPrimitive(PrimitiveElement element,
                                const QStyleOption *option,
                                QPainter *painter,
                                const QWidget *widget) const {

    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void WindowStyle::drawControl(ControlElement element,
                              const QStyleOption *option,
                              QPainter *painter,
                              const QWidget *widget) const {

    QProxyStyle::drawControl(element, option, painter, widget);
}

int WindowStyle::pixelMetric(PixelMetric metric,
                             const QStyleOption *option,
                             const QWidget *widget) const {

    return QProxyStyle::pixelMetric(metric, option, widget);
}

CUKE_END_NAMESPACE(widget)
