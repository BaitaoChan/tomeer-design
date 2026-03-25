#include <QPainter>
#include <QStyleOption>
#include <QMainWindow>

#include "CukeWindowStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeWindowStyle::CukeWindowStyle(QStyle *style)
    : QProxyStyle(style),
      CukeHub(this) {
}

CukeWindowStyle::~CukeWindowStyle() = default;

void CukeWindowStyle::drawPrimitive(PrimitiveElement element,
                                    const QStyleOption *option,
                                    QPainter *painter,
                                    const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void CukeWindowStyle::drawControl(ControlElement element,
                                  const QStyleOption *option,
                                  QPainter *painter,
                                  const QWidget *widget) const {
    QProxyStyle::drawControl(element, option, painter, widget);
}

void CukeWindowStyle::drawComplexControl(ComplexControl control,
                                         const QStyleOptionComplex *option,
                                         QPainter *painter,
                                         const QWidget *widget) const {
    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

int CukeWindowStyle::pixelMetric(PixelMetric metric,
                                 const QStyleOption *option,
                                 const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

CUKE_NAMESPACE_END(pub)
