#include <QStyleOption>
#include <QPainter>

#include "CukeMenuStyle.h"
#include "CukeMenu.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeMenuStyle::CukeMenuStyle(QStyle *style)
    : QProxyStyle(style) {
}

CukeMenuStyle::~CukeMenuStyle() = default;

void CukeMenuStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto menu = qobject_cast<const CukeMenu *>(widget);
    if (element == PE_PanelMenu) {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing);

        constexpr int radius = 6;
        constexpr int margin = 6;

        const QRect rect = option->rect.adjusted(margin, 0, -margin, -margin);

        painter->setPen(Qt::NoPen);
        painter->setBrush(CUKE_THEME->getThemeColor(menu->getThemeMode(), CukeThemeType::ComboBoxView));
        painter->drawRoundedRect(rect, radius, radius);

        painter->restore();
        return;
    }
    if (element == PE_FrameMenu)
        return;
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void CukeMenuStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto menu = qobject_cast<const CukeMenu *>(widget);

    if (element == CE_MenuItem && menu) {
        const auto opt = qstyleoption_cast<const QStyleOptionMenuItem *>(option);

        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

        const QRect rect = opt->rect;

        // 选中背景
        if (opt->state & State_Selected) {
            painter->setPen(Qt::NoPen);
            painter->setBrush(CUKE_THEME->getThemeColor(menu->getThemeMode(),
                                                    CukeThemeType::ComboBoxItem));
            painter->drawRoundedRect(rect.adjusted(8, 2, -2, -2), 4, 4);
        }

        // 左侧激光指示
        if (opt->state & State_Selected) {
            const QRect lRect(rect.left() + 10, rect.top() + 4, 3, rect.height() - 8);

            painter->setPen(Qt::NoPen);
            painter->setBrush(CUKE_THEME->getThemeColor(menu->getThemeMode(), CukeThemeType::Check));
            painter->drawRoundedRect(lRect, 2, 2);
        }

        // 文本
        painter->setPen(CUKE_THEME->getThemeColor(menu->getThemeMode(), CukeThemeType::Text));
        painter->drawText(rect.adjusted(16, 0, -2, 0),
                          Qt::AlignVCenter | Qt::AlignLeft,
                          opt->text);

        painter->restore();
        return;
    }
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
    if (type == CT_Menu) {
        s.rheight() += 6;
    }
    if (type == CT_MenuItem)
        s.rheight() += 6;
    return s;
}

CUKE_NAMESPACE_END(pub)