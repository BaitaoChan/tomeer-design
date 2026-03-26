#include <QStyleoption>
#include <QPainter>
#include <QPainterPath>

#include "CukeToolButtonStyle.h"
#include "CukeToolButton.h"
#include "CukePainter.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeToolButtonStyle::CukeToolButtonStyle(QStyle *style)
    : QProxyStyle(style),
      CukeHub(this) {
}

CukeToolButtonStyle::~CukeToolButtonStyle() = default;

void CukeToolButtonStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    if (element == PE_PanelButtonBevel) {
        const auto toolButton = qobject_cast<const CukeToolButton *>(widget);
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        // 背景
        if (toolButton->getBgColorUsedFlag()) {
            if (toolButton->getStateOverride()) {
                if (toolButton->getHover() || toolButton->getPressed()) {
                    painter->setBrush(toolButton->getBgColor());
                }
            } else {
                if (option->state & State_Sunken || option->state & State_MouseOver)
                    painter->setBrush(toolButton->getBgColor());
            }
        } else {
            if (toolButton->getStateOverride()) {
                if (toolButton->getPressed())
                    painter->setBrush(cTheme->getThemeColor(getThemeMode(), CukeThemeType::Press));
                else if (toolButton->getHover())
                    painter->setBrush(cTheme->getThemeColor(getThemeMode(), CukeThemeType::Hover));
            } else {
                if (option->state & State_Sunken)
                    painter->setBrush(cTheme->getThemeColor(getThemeMode(), CukeThemeType::Press));
                else if (option->state & State_MouseOver)
                    painter->setBrush(cTheme->getThemeColor(getThemeMode(), CukeThemeType::Hover));
            }
        }
        cPainter->drawRoundedRect(option->rect, painter, toolButton->getBorderRadius(), toolButton->getBorderRadius(), toolButton->getSideFlag());
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