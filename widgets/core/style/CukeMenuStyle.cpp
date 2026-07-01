#include <QStyleOption>

#include "CukeMenuStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeMenuStyle::CukeMenuStyle(QStyle *style)
    : QProxyStyle(style) {
}

CukeMenuStyle::~CukeMenuStyle() = default;

void CukeMenuStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    if (element == PE_PanelMenu) {
        return;
    }
    if (element == PE_FrameMenu)
        return;
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void CukeMenuStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    if (element == CE_MenuItem)
        return;
    if (element == CE_MenuEmptyArea)
        return;
    QProxyStyle::drawControl(element, option, painter, widget);
}

int CukeMenuStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    if (metric == PM_MenuPanelWidth)
        ;
    return QProxyStyle::pixelMetric(metric, option, widget);
}

QSize CukeMenuStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const {
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == CT_Menu)
        ;
    if (type == CT_MenuItem)
        ;
    return s;
}

CUKE_NAMESPACE_END(pub)