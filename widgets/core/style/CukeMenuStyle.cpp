#include <QStyleOption>
#include <QPainter>

#include "CukeMenuStyle.h"
#include "CukeMenu.h"

CUKE_NAMESPACE_BEGIN(pub)
MenuStyle::MenuStyle(QStyle *style)
    : QProxyStyle(style) {
}

MenuStyle::~MenuStyle() = default;

void MenuStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto menu = qobject_cast<const Menu *>(widget);
    if (element == PE_PanelMenu) {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing);

        constexpr int radius = 6;
        constexpr int margin = 6;

        const QRect rect = option->rect.adjusted(margin, 0, -2 * margin, -margin);

        painter->setPen(Qt::NoPen);
        painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::ComboBoxView));
        painter->drawRoundedRect(rect, radius, radius);

        painter->restore();
        return;
    }
    if (element == PE_FrameMenu)
        return;
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void MenuStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto menu = qobject_cast<const Menu *>(widget);

    if (element == CE_MenuItem) {
        const auto opt = qstyleoption_cast<const QStyleOptionMenuItem *>(option);

        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

        const QRect rect = opt->rect;

        // 选中背景
        if (opt->state & State_Selected) {
            painter->setPen(Qt::NoPen);
            painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::ComboBoxItem));
            painter->drawRoundedRect(rect.adjusted(6, 1, -2, -1), 4, 4);
        }

        // 左侧激光指示
        if (opt->state & State_Selected) {
            const QRect lRect(rect.left() + 8, rect.top() + 4, 3, rect.height() - 8);

            painter->setPen(Qt::NoPen);
            painter->setBrush(CUKE_THEME->getThemeColor(menu->getThemeMode(), ThemeType::Check));
            painter->drawRoundedRect(lRect, 2, 2);
        }

        // 文本
        painter->setPen(CUKE_THEME->getThemeColor(menu->getThemeMode(), ThemeType::Text));
        painter->drawText(rect.adjusted(16, 0, -2, 0), Qt::AlignVCenter | Qt::AlignLeft, opt->text);

        painter->restore();
        return;
    }
    if (element == CE_MenuEmptyArea)
        return;
    QProxyStyle::drawControl(element, option, painter, widget);
}

int MenuStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    if (metric == PM_MenuPanelWidth)
        ;
    return QProxyStyle::pixelMetric(metric, option, widget);
}

QSize MenuStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const {
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == CT_Menu) {
        s.rheight() += 6;
    }
    if (type == CT_MenuItem)
        s.rheight() += 6;
    return s;
}

CUKE_NAMESPACE_END(pub)