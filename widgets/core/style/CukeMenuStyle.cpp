#include <QStyleOption>

#include "CukeMenuStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeMenuStyle::CukeMenuStyle(QStyle *style)
    : QProxyStyle(style) {
}

CukeMenuStyle::~CukeMenuStyle() = default;

void CukeMenuStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}
void CukeMenuStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawControl(element, option, painter, widget);
}
int CukeMenuStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}
CUKE_NAMESPACE_END(pub)