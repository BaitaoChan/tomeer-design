#include <QStyleOption>
#include <QStyleOptionSlider>
#include <QPainter>

#include "scroll_bar_style.h"
#include "theme.h"

TOMEER_NAMESPACE_BEGIN()
ScrollBarStyle::ScrollBarStyle(QStyle *style)
    : QProxyStyle(style) {
}

ScrollBarStyle::~ScrollBarStyle() = default;

void ScrollBarStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void ScrollBarStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const {
    if (control == CC_ScrollBar) {
        const auto opt = qstyleoption_cast<const QStyleOptionSlider *>(option);
        if (opt->minimum >= opt->maximum)
            return;

        QRectF hRect = subControlRect(CC_ScrollBar, opt, SC_ScrollBarSlider, widget);
        const qreal _width = opt->state & State_MouseOver ? 6 : 4;
        if (opt->orientation == Qt::Vertical) {
            hRect.setLeft(hRect.center().x() - _width / 2);
            hRect.setWidth(_width);
            hRect.adjust(0, 2, 0, -2);
        } else {
            hRect.setTop(hRect.center().y() - _width / 2);
            hRect.setHeight(_width);
            hRect.adjust(2, 0, -2, 0);
        }

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(TOMEER_THEME->getThemeColor(opt->state & State_MouseOver ? ThemeType::ScrollBarHandleHover : ThemeType::ScrollBarHandle));
        painter->drawRoundedRect(hRect, _width / 2, _width / 2);
        painter->restore();
        return;
    }
    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

void ScrollBarStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawControl(element, option, painter, widget);
}

int ScrollBarStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    if (metric == PM_ScrollBarExtent)
        return 10;
    if (metric == PM_ScrollBarSliderMin)
        return 36;
    return QProxyStyle::pixelMetric(metric, option, widget);
}

QRect ScrollBarStyle::subControlRect(ComplexControl control, const QStyleOptionComplex *option, SubControl subControl, const QWidget *widget) const {
    if (control == CC_ScrollBar) {
        const auto opt = qstyleoption_cast<const QStyleOptionSlider *>(option);
        if (subControl == SC_ScrollBarGroove)
            return opt->rect;
        if (subControl == SC_ScrollBarSubLine || subControl == SC_ScrollBarAddLine)
            return {};

        const int _length = opt->orientation == Qt::Vertical ? opt->rect.height() : opt->rect.width();
        if (_length <= 0)
            return {};

        const int minLength = qMin(pixelMetric(PM_ScrollBarSliderMin, option, widget), _length);
        const qreal range = opt->maximum - opt->minimum;
        int hLength = _length;
        if (range > 0) {
            if (opt->pageStep > 0)
                hLength = qRound(opt->pageStep * _length / (range + opt->pageStep));
            else
                hLength = minLength;
            hLength = qBound(minLength, hLength, _length);
        }

        const int hPosition = sliderPositionFromValue(opt->minimum, opt->maximum, opt->sliderPosition, _length - hLength, opt->upsideDown);

        QRect hRect, subRect, addRect;
        if (opt->orientation == Qt::Vertical) {
            hRect = QRect(opt->rect.x(), opt->rect.y() + hPosition, opt->rect.width(), hLength);
            subRect = QRect(opt->rect.x(), opt->rect.y(), opt->rect.width(), hPosition);
            addRect = QRect(opt->rect.x(), hRect.bottom() + 1, opt->rect.width(), _length - hPosition - hLength);
        } else {
            hRect = QRect(opt->rect.x() + hPosition, opt->rect.y(), hLength, opt->rect.height());
            subRect = QRect(opt->rect.x(), opt->rect.y(), hPosition, opt->rect.height());
            addRect = QRect(hRect.right() + 1, opt->rect.y(), _length - hPosition - hLength, opt->rect.height());
        }

        if (subControl == SC_ScrollBarSlider)
            return hRect;
        if (subControl == (opt->upsideDown ? SC_ScrollBarAddPage : SC_ScrollBarSubPage))
            return subRect;
        if (subControl == (opt->upsideDown ? SC_ScrollBarSubPage : SC_ScrollBarAddPage))
            return addRect;
    }
    return QProxyStyle::subControlRect(control, option, subControl, widget);
}

QStyle::SubControl ScrollBarStyle::hitTestComplexControl(ComplexControl control, const QStyleOptionComplex *option, const QPoint &position, const QWidget *widget) const {
    if (control == CC_ScrollBar) {
        if (subControlRect(control, option, SC_ScrollBarSlider, widget).contains(position))
            return SC_ScrollBarSlider;
        if (subControlRect(control, option, SC_ScrollBarSubPage, widget).contains(position))
            return SC_ScrollBarSubPage;
        if (subControlRect(control, option, SC_ScrollBarAddPage, widget).contains(position))
            return SC_ScrollBarAddPage;
    }
    return QProxyStyle::hitTestComplexControl(control, option, position, widget);
}

TOMEER_NAMESPACE_END
