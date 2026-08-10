#include <QStyleoption>
#include <QPainter>

#include "tool_bar.h"
#include "tool_button.h"
#include "tool_bar_style.h"

#include "painter.h"
#include "theme.h"

TOMEER_NAMESPACE_BEGIN()
ToolBarStyle::ToolBarStyle(QStyle *style)
    : QProxyStyle(style) {
}

ToolBarStyle::~ToolBarStyle() = default;

void ToolBarStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto toolBar = qobject_cast<const ToolBar *>(widget);
    if (element == PE_IndicatorToolBarHandle) {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(TOMEER_THEME->getThemeColor(ThemeType::ToolBarHandle)));

        int radius, width, height, x, y;
        radius = 1;
        if (toolBar->orientation() == Qt::Horizontal) {
            width = 2, height = toolBar->rect().height() / 2, x = option->rect.center().x() - width / 2, y =
                    option->rect.center().y() - height / 2;
        } else {
            width = toolBar->rect().width() / 2, height = 2, x = option->rect.center().x() - width / 2, y =
                    option->rect.center().y() - height / 2;
        }

        TOMEER_PAINTER->drawRoundedRect(QRect(x, y, width, height),
                                  painter, radius, radius, GeometryType::All);
        painter->restore();
        return;
    }
    if (element == PE_FrameMenu)
        return;
    return QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void ToolBarStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto toolBar = qobject_cast<const ToolBar *>(widget);
    if (element == CE_ToolBar) {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing);
        if (toolBar && toolBar->isFloating()) {
            // 悬浮
            int radius = 4;
            painter->setPen(Qt::NoPen);
            painter->setBrush(TOMEER_THEME->getThemeColor(toolBar->getThemeMode(), ThemeType::ToolBarBg));
            painter->drawRoundedRect(toolBar->rect(), radius, radius);
        } else {
            // 停靠
        }
        painter->restore();
        return;
    }
    return QProxyStyle::drawControl(element, option, painter, widget);
}

void ToolBarStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const {
    return QProxyStyle::drawComplexControl(control, option, painter, widget);
}

int ToolBarStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

QSize ToolBarStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const {
    return QProxyStyle::sizeFromContents(type, option, size, widget);
}

TOMEER_NAMESPACE_END