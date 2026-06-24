#include <QStyleoption>
#include <QPainter>

#include "CukeToolBar.h"
#include "CukeToolButton.h"
#include "CukeToolBarStyle.h"

#include "CukePainter.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeToolBarStyle::CukeToolBarStyle(QStyle *style)
    : QProxyStyle(style) {
}

CukeToolBarStyle::~CukeToolBarStyle() = default;

void CukeToolBarStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto toolBar = qobject_cast<const CukeToolBar *>(widget);
    if (element == PE_IndicatorToolBarHandle) {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(cTheme->getThemeColor(toolBar->getThemeMode(), CukeThemeType::IndicatorToolBarHandle)));

        int _radius, _width, _height, x, y;
        _radius = 1;
        if (toolBar->orientation() == Qt::Horizontal) {
            _width = 2, _height = toolBar->rect().height() / 2, x = option->rect.center().x() - _width / 2, y =
                    option->rect.center().y() - _height / 2;
        } else {
            _width = toolBar->rect().width() / 2, _height = 2, x = option->rect.center().x() - _width / 2, y =
                    option->rect.center().y() - _height / 2;
        }

        cPainter->drawRoundedRect(QRect(x, y, _width, _height),
                                  painter, _radius, _radius, CukeGeometryType::All);
        painter->restore();
        return;
    }
    if (element == PE_FrameMenu)
        return;
    return QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void CukeToolBarStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto toolBar = qobject_cast<const CukeToolBar *>(widget);
    if (element == CE_ToolBar)
        return;
    return QProxyStyle::drawControl(element, option, painter, widget);
}

void CukeToolBarStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const {
    return QProxyStyle::drawComplexControl(control, option, painter, widget);
}

int CukeToolBarStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

QSize CukeToolBarStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const {
    return QProxyStyle::sizeFromContents(type, option, size, widget);
}

CUKE_NAMESPACE_END(pub)