#include <QPainter>
#include <QStyleOption>
#include <QMainWindow>

#include "window_style.h"
#include "theme.h"

TOMEER_NAMESPACE_BEGIN()
WindowStyle::WindowStyle(QStyle *style)
    : QProxyStyle(style) {
}

WindowStyle::~WindowStyle() = default;

void WindowStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void WindowStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    if (element == CE_RubberBand) {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::RubberBand));
        painter->drawRect(option->rect);
        painter->restore();
        return;
    }
    QProxyStyle::drawControl(element, option, painter, widget);
}

void WindowStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

int WindowStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

TOMEER_NAMESPACE_END