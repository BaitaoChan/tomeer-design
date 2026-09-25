#include <QStyleOption>
#include <QPainter>

#include "check_box_style.h"
#include "check_box.h"
#include "theme.h"

TOMEER_NAMESPACE_BEGIN()
CheckBoxStyle::CheckBoxStyle(QStyle *style)
    : QProxyStyle(style) {
}

CheckBoxStyle::~CheckBoxStyle() = default;

void CheckBoxStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto checkBox = qobject_cast<const CheckBox *>(widget);
    if (element == CE_CheckBox) {
        const auto opt = qstyleoption_cast<const QStyleOptionButton *>(option);
        const int indicatorSize = QFontMetrics(widget->font()).height();

        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

        // 复选框绘制
        QRect indicatorRect(opt->rect.x(), opt->rect.y() + (opt->rect.height() - indicatorSize) / 2, indicatorSize, indicatorSize);
        indicatorRect = visualRect(opt->direction, opt->rect, indicatorRect);
        QRect cRect = indicatorRect.adjusted(1, 1, -1, -1);
        painter->setPen(TOMEER_THEME->getThemeColor(ThemeType::BorderAlpha));

        if (opt->state & State_Enabled) {
            if (opt->state & State_On) {
                painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::CheckAlpha));
            } else if (opt->state & State_NoChange) {
                painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::CheckAlpha));
            } else {
                if (opt->state & State_MouseOver)
                    painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::CheckBoxHover));
                else
                    painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::CheckBox));
            }
        }
        painter->drawRoundedRect(cRect, checkBox->getBorderRadius(), checkBox->getBorderRadius());

        // 勾选绘制
        painter->save();
        painter->setPen(TOMEER_THEME->getThemeColor(ThemeType::Dark, ThemeType::Text));
        QFont font("tomeer");
        font.setPixelSize(indicatorSize);
        painter->setFont(font);
        if (opt->state & State_On)
            painter->drawText(cRect, Qt::AlignCenter, QChar(IconType::Checkmark));
        else if (opt->state & State_NoChange) {
            painter->setPen(QPen(TOMEER_THEME->getThemeColor(ThemeType::Dark, ThemeType::Text), 2));
            painter->drawLine(cRect.left() + 2, cRect.center().y(), cRect.right() - 2, cRect.center().y());
        }
        painter->restore();

        // 图标和文字绘制
        QRect tRect = opt->rect.adjusted(indicatorSize + pixelMetric(PM_CheckBoxLabelSpacing, opt, widget), 0, 0, 0);
        if (!opt->icon.isNull()) {
            QRect iRect(tRect.x(), tRect.y() + (tRect.height() - opt->iconSize.height()) / 2, opt->iconSize.width(), opt->iconSize.height());
            if (checkBox->getIcon() != IconType::None) {
                painter->save();
                if (opt->state & State_Enabled)
                    painter->setPen(TOMEER_THEME->getThemeColor(ThemeType::Text));
                else
                    painter->setPen(TOMEER_THEME->getThemeColor(ThemeType::TextDisable));
                font.setPixelSize(opt->iconSize.height());
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QChar(checkBox->getIcon()));
                painter->restore();
            } else if (opt->state & State_Enabled)
                opt->icon.paint(painter, iRect, Qt::AlignCenter);
            tRect.adjust(opt->iconSize.width() + 4, 0, 0, 0);
        }
        if (!opt->text.isEmpty()) {
            if (opt->state & State_Enabled)
                painter->setPen(TOMEER_THEME->getThemeColor(ThemeType::Text));
            else
                painter->setPen(TOMEER_THEME->getThemeColor(ThemeType::TextDisable));
            painter->drawText(tRect, Qt::AlignLeft | Qt::AlignVCenter, opt->text);
        }

        painter->restore();
        return;
    }

    QProxyStyle::drawControl(element, option, painter, widget);
}

int CheckBoxStyle::pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const {
    if (metric == PM_IndicatorWidth || metric == PM_IndicatorHeight)
        return QFontMetrics(widget->font()).height();
    if (metric == PM_CheckBoxLabelSpacing)
        return 4;
    return QProxyStyle::pixelMetric(metric, option, widget);
}

TOMEER_NAMESPACE_END
