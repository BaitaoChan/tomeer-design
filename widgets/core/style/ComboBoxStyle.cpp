#include "ComboBoxStyle.h"

#include "ComboBox.h"

CUKE_BEGIN_NAMESPACE(widget)
ComboBoxStyle::ComboBoxStyle(QStyle *style)
    : ContextMixin(style) {
}

ComboBoxStyle::~ComboBoxStyle() = default;

void ComboBoxStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                                  QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void ComboBoxStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter,
                                const QWidget *widget) const {
    // QFrame
    if (element == CE_ShapedFrame) {
        if (widget && qobject_cast<const QFrame *>(widget)) {
            int _radius = 6;
            painter->save();
            painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

            // 阴影区域
            QRect r(option->rect.x() + 6, option->rect.y(),
                    option->rect.width() - 12, option->rect.height() - 6);
            painter->setBrush(pThemeColor(_themeMode, ComboBoxView));
            painter->setPen(Qt::NoPen);
            painter->drawRoundedRect(r, _radius, _radius);
            painter->restore();
        }
        return;
    }

    if (element == CE_ComboBoxLabel) {
        const auto opt =
                qstyleoption_cast<const QStyleOptionComboBox *>(option);
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(pThemeColor(_themeMode, Text));
        painter->drawText(
            option->rect.adjusted(
                8, 0, 0, 0
            ), Qt::AlignVCenter | Qt::AlignLeft, opt->currentText);
        painter->restore();
        return;
    }
    QProxyStyle::drawControl(element, option, painter, widget);
}

void ComboBoxStyle::drawComplexControl(
    ComplexControl control,
    const QStyleOptionComplex *option,
    QPainter *painter,
    const QWidget *widget) const {
    if (control == CC_ComboBox) {
        const auto *opt = qstyleoption_cast<const QStyleOptionComboBox *>(option);
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        int _radius = 6;
        const QRect fr = subControlRect(
            CC_ComboBox, opt, SC_ComboBoxFrame, widget);

        // 背景
        if (opt->state & State_MouseOver)
            painter->setBrush(pThemeColor(_themeMode, HoverAlpha));
        else
            painter->setBrush(pThemeColor(_themeMode, DefaultAlpha));
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(fr.adjusted(1, 1, -1, -1), _radius, _radius);

        painter->restore();
        return;
    }

    QProxyStyle::drawComplexControl(control, option, painter, widget);
}


int ComboBoxStyle::pixelMetric(PixelMetric metric, const QStyleOption *option,
                               const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

CUKE_END_NAMESPACE(widget)