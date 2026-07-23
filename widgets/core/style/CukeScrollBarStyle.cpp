#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>

#include "CukeScrollBarStyle.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN(pub)
ScrollBarStyle::ScrollBarStyle(QStyle *style)
    : QProxyStyle(style) {
}

ScrollBarStyle::~ScrollBarStyle() = default;

void ScrollBarStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void ScrollBarStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const {
    if (control == CC_ScrollBar) {
        return;
    }
    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

void ScrollBarStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawControl(element, option, painter, widget);
}

int ScrollBarStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

CUKE_NAMESPACE_END(pub)