#include <QStyleoption>
#include <QPainter>

#include "CukeMenuBar.h"
#include "CukeMenuBarStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeMenuBarStyle::CukeMenuBarStyle(QStyle *style)
    : QProxyStyle(style) {
}

CukeMenuBarStyle::~CukeMenuBarStyle() = default;

void CukeMenuBarStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void CukeMenuBarStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto menuBar = qobject_cast<const CukeMenuBar *>(widget);
    if (element == CE_MenuBarEmptyArea)
        return;
    if (element == CE_MenuBarItem) {
        int radius = 4;
        const auto opt =
                qstyleoption_cast<const QStyleOptionMenuItem *>(option);
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        painter->setPen(Qt::NoPen);
        if (opt->state & State_Enabled) {
            if (opt->state & State_Selected)
                painter->setBrush(CUKE_THEME->getThemeColor(CukeThemeType::HoverAlpha));
            else if (opt->state & State_Sunken)
                painter->setBrush(CUKE_THEME->getThemeColor(CukeThemeType::PressAlpha));
        }
        painter->drawRoundedRect(opt->rect.adjusted(1, 1, -1, -1), radius, radius);

        painter->setPen(CUKE_THEME->getThemeColor(CukeThemeType::Text));
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

QSize CukeMenuBarStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const {
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == CT_MenuBarItem) {
        if (const auto opt =
                qstyleoption_cast<const QStyleOptionMenuItem *>(option)) {
            if (const auto menuBar = qobject_cast<const QMenuBar *>(widget)) {
                s.setHeight(menuBar->height());
                s.setWidth(qRound(QFontMetrics(opt->font).horizontalAdvance(opt->text) + menuBar->height() * 0.8));
            }
        }
    }
    return s;
}

CUKE_NAMESPACE_END(pub)