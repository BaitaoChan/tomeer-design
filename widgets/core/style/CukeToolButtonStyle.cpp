#include <QStyleoption>
#include <QPainter>
#include <QPainterPath>

#include "CukeToolButtonStyle.h"
#include "CukeToolButton.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeToolButtonStyle, int, BorderRadius)
CukeToolButtonStyle::CukeToolButtonStyle(QStyle *style)
    : CukeContextMixin(style),
      _pBorderRadius(0) {
}

CukeToolButtonStyle::~CukeToolButtonStyle() = default;

void CukeToolButtonStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    if (element == PE_PanelButtonBevel) {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        // 背景
        if (option->state & State_Enabled) {
            if (option->state & State_Sunken) {
                painter->setBrush(cTheme->getThemeColor(_themeMode, CukeThemeType::Press));
            } else if (option->state & State_MouseOver) {
                painter->setBrush(cTheme->getThemeColor(_themeMode, CukeThemeType::Hover));
            }
        }
        painter->drawRoundedRect(option->rect, _pBorderRadius, _pBorderRadius);
        painter->restore();
        return;
    }
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void CukeToolButtonStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

int CukeToolButtonStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

CUKE_NAMESPACE_END(pub)