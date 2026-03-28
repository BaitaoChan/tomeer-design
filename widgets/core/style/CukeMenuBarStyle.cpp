#include <QStyleoption>
#include <QPainter>

#include "CukeMenuBarStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeMenuBarStyle::CukeMenuBarStyle(QStyle *style)
    : QProxyStyle(style),
      CukeScope(this) {
}

CukeMenuBarStyle::~CukeMenuBarStyle() = default;

void CukeMenuBarStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void CukeMenuBarStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    if (element == CE_MenuBarEmptyArea)
        return;
    if (element == CE_MenuBarItem) {
        int _radius = 4;
        const auto opt =
                qstyleoption_cast<const QStyleOptionMenuItem *>(option);
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        painter->setPen(Qt::NoPen);
        if (opt->state & State_Enabled) {
            if (opt->state & State_Selected)
                painter->setBrush(cTheme->getThemeColor(getThemeMode(), CukeThemeType::HoverAlpha));
            else if (opt->state & State_Sunken)
                painter->setBrush(cTheme->getThemeColor(getThemeMode(), CukeThemeType::PressAlpha));
        }
        painter->drawRoundedRect(opt->rect.adjusted(3, 3, -3, -3), _radius, _radius);

        painter->setPen(cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text));
        painter->drawText(opt->rect.adjusted(1, 1, -1, -1), Qt::AlignCenter, opt->text);

        painter->restore();
        return;
    }
    QProxyStyle::drawControl(element, option, painter, widget);
}

void CukeMenuBarStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

int CukeMenuBarStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

CUKE_NAMESPACE_END(pub)