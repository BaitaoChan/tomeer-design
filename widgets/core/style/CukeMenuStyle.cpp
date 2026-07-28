#include <QStyleOption>
#include <QPainter>

#include "CukeMenuStyle.h"
#include "CukeMenu.h"
#include "CukeAction.h"

CUKE_NAMESPACE_BEGIN(pub)
MenuStyle::MenuStyle(QStyle *style)
    : QProxyStyle(style) {
}

MenuStyle::~MenuStyle() = default;

void MenuStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
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
        const auto qAction = menu->actionAt(opt->rect.center());
        const auto action = qobject_cast<const Action *>(qAction);
        const auto childMenu = qobject_cast<const Menu *>(qAction->menu());

        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

        QRect rect = opt->rect;

        // 分隔线
        if (opt->menuItemType == QStyleOptionMenuItem::Separator) {
            painter->setPen(CUKE_THEME->getThemeColor(ThemeType::Separator));
            painter->drawLine(rect.left() + 12, rect.center().y(), rect.right() - 8, rect.center().y());
            painter->restore();
            return;
        }

        // 选中背景
        if (opt->state & State_Enabled && opt->state & State_Selected) {
            painter->save();
            painter->setPen(Qt::NoPen);
            painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::ComboBoxItem));
            painter->drawRoundedRect(rect.adjusted(6, 1, -2, -1), 4, 4);
            painter->restore();
        }

        // 左侧激光指示
        if (opt->state & State_Enabled && opt->state & State_Selected) {
            const QRect lRect(rect.left() + 8, rect.top() + 4, 3, rect.height() - 8);
            painter->save();
            painter->setPen(Qt::NoPen);
            painter->setBrush(CUKE_THEME->getThemeColor(menu->getThemeMode(), ThemeType::Check));
            painter->drawRoundedRect(lRect, 2, 2);
            painter->restore();
        }

        // 文字图标绘制
        painter->setPen(opt->state & State_Enabled ? CUKE_THEME->getThemeColor(ThemeType::Text) : CUKE_THEME->getThemeColor(ThemeType::TextDisable));
        painter->setBrush(opt->state & State_Enabled ? CUKE_THEME->getThemeColor(ThemeType::Text) : CUKE_THEME->getThemeColor(ThemeType::TextDisable));

        constexpr int spacing = 4;
        constexpr int left = 12 + spacing;
        constexpr int right = 2 + spacing;
        constexpr qreal scale = 1.0;
        const int iWidth = QFontMetrics(opt->font).height();
        const int tWidth = QFontMetrics(opt->font).horizontalAdvance(opt->text.split(QLatin1Char('\t')).value(0));
        const int sWidth = QFontMetrics(opt->font).horizontalAdvance(opt->text.split(QLatin1Char('\t')).value(1));


        // 内容
        QRect lRect = rect.adjusted(left, 0, -right, 0);
        lRect.setHeight(iWidth);
        lRect.moveCenter({lRect.center().x(), rect.center().y()});

        int _lLength = 0;
        int _rLength = 0;

        // 图标
        if (!opt->icon.isNull() || opt->menuHasCheckableItems) {
            const QRect iRect = QRect(lRect.topLeft(), QSize(iWidth, iWidth));

            if (opt->checkType != QStyleOptionMenuItem::NotCheckable && opt->checked && opt->icon.isNull()) {
                painter->save();
                painter->setPen(Qt::NoPen);
                if (opt->state & State_Enabled)
                    painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::CheckAlpha));
                else
                    painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::Disable));
                painter->drawRoundedRect(iRect.adjusted(1, 1, -1, -1), 3, 3);
                painter->restore();
            }

            painter->save();
            if (!(opt->state & State_Enabled)) {
                painter->setPen(CUKE_THEME->getThemeColor(ThemeType::TextDisable));
                painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::TextDisable));
            } else if (opt->checkType != QStyleOptionMenuItem::NotCheckable && opt->checked && !opt->icon.isNull()) {
                painter->setPen(CUKE_THEME->getThemeColor(ThemeType::Check));
                painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::Check));
            } else if (opt->checkType != QStyleOptionMenuItem::NotCheckable && opt->checked) {
                painter->setPen(CUKE_THEME->getThemeColor(ThemeType::Window));
                painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::Window));
            } else {
                painter->setPen(CUKE_THEME->getThemeColor(ThemeType::Text));
                painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::Text));
            }
            QFont font("Cuke");
            font.setPixelSize(qRound(iWidth * scale));
            painter->setFont(font);
            if (action && action->getCukeIcon() != IconType::None)
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(action->getCukeIcon())));
            else if (childMenu && childMenu->getCukeIcon() != IconType::None)
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(childMenu->getCukeIcon())));
            else if (!opt->icon.isNull())
                opt->icon.paint(painter, iRect, Qt::AlignCenter);
            else if (opt->checked)
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(IconType::Checkmark)));
            painter->restore();

            _lLength += iWidth;
            _lLength += spacing;
        }
        // 文本
        if (!opt->text.split(QLatin1Char('\t')).value(0).isEmpty()) {
            const QRect tRect = QRect(QPoint(lRect.topLeft().x() + _lLength, lRect.topLeft().y()), QSize(tWidth, iWidth));
            painter->setPen(opt->state & State_Enabled ? CUKE_THEME->getThemeColor(ThemeType::Text) : CUKE_THEME->getThemeColor(ThemeType::TextDisable));
            painter->drawText(tRect, Qt::AlignVCenter | Qt::AlignLeft, opt->text.split(QLatin1Char('\t')).value(0));
        }
        // 拓展菜单
        if (opt->menuItemType == QStyleOptionMenuItem::SubMenu) {
            _rLength += iWidth;
            QRect aRect = QRect(QPoint(lRect.topRight().x() - _rLength, lRect.topRight().y()), QSize(iWidth, iWidth));
            _rLength += spacing;
            painter->save();
            painter->setPen(opt->state & State_Enabled ? CUKE_THEME->getThemeColor(ThemeType::Text) : CUKE_THEME->getThemeColor(ThemeType::TextDisable));
            QFont font("Cuke");
            font.setPixelSize(qRound(iWidth * scale));
            painter->setFont(font);
            painter->drawText(aRect, Qt::AlignCenter, QString(QChar(IconType::ChevronRight)));
            painter->restore();
        }
        // 快捷键
        if (!opt->text.split(QLatin1Char('\t')).value(1).isEmpty()) {
            _rLength += sWidth;
            const QRect sRect = QRect(QPoint(lRect.topRight().x() - _rLength, lRect.topRight().y()), QSize(sWidth, iWidth));
            painter->save();
            painter->setPen(opt->state & State_Enabled ? CUKE_THEME->getThemeColor(ThemeType::Text) : CUKE_THEME->getThemeColor(ThemeType::TextDisable));
            painter->drawText(sRect, Qt::AlignVCenter | Qt::AlignRight, opt->text.split(QLatin1Char('\t')).value(1));
            painter->restore();
        }

        painter->restore();
        return;
    }
    if (element == CE_MenuEmptyArea)
        return;
    QProxyStyle::drawControl(element, option, painter, widget);
}

int MenuStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    if (metric == PM_SmallIconSize)
        if (const auto *menu = qobject_cast<const Menu *>(widget))
            return menu->fontMetrics().height();
    return QProxyStyle::pixelMetric(metric, option, widget);
}

QSize MenuStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const {
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == CT_Menu) {
        s.rheight() += 6;
    }
    // Menu 和 SubMenu 的 Item 保持高度一致
    if (type == CT_MenuItem) {
        s.rheight() += 6;
        const auto opt = qstyleoption_cast<const QStyleOptionMenuItem *>(option);
        if (opt->menuItemType != QStyleOptionMenuItem::Separator)
            s.setHeight(opt->fontMetrics.height() + 12);
    }
    return s;
}

CUKE_NAMESPACE_END(pub)