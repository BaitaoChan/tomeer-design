#include <QPainterPath>
#include <QPainter>
#include <QStyleOptionComboBox>

#include "CukeComboBoxStyle.h"
#include "CukeComboBox.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN(pub)
ComboBoxStyle::ComboBoxStyle(QStyle *style)
    : QProxyStyle(style) {
}

ComboBoxStyle::~ComboBoxStyle() = default;

void ComboBoxStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void ComboBoxStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const ComboBox *combo = nullptr;
    for (const QWidget *w = widget; w; w = w->parentWidget()) {
        combo = qobject_cast<const ComboBox *>(w);
        if (combo) break;
    }
    // QFrame
    if (element == CE_ShapedFrame) {
        if (widget && qobject_cast<const QFrame *>(widget)) {
            int radius = 6;
            painter->save();
            painter->setRenderHints(QPainter::Antialiasing);

            // 阴影区域
            QRect r(option->rect.x() + 6, option->rect.y(),
                    option->rect.width() - 12, option->rect.height() - 6);
            painter->setBrush(CUKE_THEME->getThemeColor(combo->getThemeMode(), ThemeType::ComboBoxView));
            painter->setPen(Qt::NoPen);
            painter->drawRoundedRect(r, radius, radius);
            painter->restore();
        }
        return;
    }

    if (element == CE_ComboBoxLabel) {
        const auto opt = qstyleoption_cast<const QStyleOptionComboBox *>(option);
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(CUKE_THEME->getThemeColor(combo->getThemeMode(), ThemeType::Text));
        painter->drawText(
            option->rect.adjusted(8, 0, 0, 0),
            Qt::AlignVCenter | Qt::AlignLeft,
            opt->currentText);
        painter->restore();
        return;
    }
    QProxyStyle::drawControl(element, option, painter, widget);
}

void ComboBoxStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const {
    if (control == CC_ComboBox) {
        const auto *opt = qstyleoption_cast<const QStyleOptionComboBox *>(option);
        const auto combo = qobject_cast<const ComboBox *>(widget);
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        int radius = 4;
        const QRect fr = subControlRect(CC_ComboBox, opt, SC_ComboBoxFrame, widget);

        // 背景
        painter->setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::Pattern), 1));
        if (opt->state & State_MouseOver)
            painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::ComboBoxHover));
        else
            painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::ComboBox));
        painter->drawRoundedRect(fr.adjusted(1, 1, -1, -1), radius, radius);

        painter->restore();
        return;
    }

    QProxyStyle::drawComplexControl(control, option, painter, widget);
}


int ComboBoxStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

CUKE_NAMESPACE_END(pub)