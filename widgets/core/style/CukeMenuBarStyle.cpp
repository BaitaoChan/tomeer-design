#include <QStyleoption>
#include <QPainter>

#include "CukeMenuBar.h"
#include "CukeMenuBarStyle.h"
#include "CukeAction.h"

CUKE_NAMESPACE_BEGIN(pub)
MenuBarStyle::MenuBarStyle(QStyle *style)
    : QProxyStyle(style) {
}

MenuBarStyle::~MenuBarStyle() = default;

void MenuBarStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void MenuBarStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto menuBar = qobject_cast<const MenuBar *>(widget);
    if (element == CE_MenuBarEmptyArea)
        return;
    if (element == CE_MenuBarItem && menuBar) {
        int radius = 4;
        const auto opt = qstyleoption_cast<const QStyleOptionMenuItem *>(option);
        const auto action = qobject_cast<const Action *>(menuBar->actionAt(opt->rect.center()));
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

        painter->setPen(Qt::NoPen);
        if (opt->state & State_Enabled) {
            if (action && action->isCheckable() && action->isChecked())
                painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::CheckAlpha));
            else if (opt->state & State_Sunken)
                painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::PressAlpha));
            else if (opt->state & State_Selected)
                painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::HoverAlpha));
        }
        painter->drawRoundedRect(opt->rect.adjusted(1, 1, -1, -1), radius, radius);

        if (!(opt->state & State_Enabled)) {
            painter->setPen(CUKE_THEME->getThemeColor(ThemeType::TextDisable));
            painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::TextDisable));
        } else if (action && action->isCheckable() && action->isChecked()) {
            painter->setPen(CUKE_THEME->getThemeColor(ThemeType::Window));
            painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::Window));
        } else {
            painter->setPen(CUKE_THEME->getThemeColor(ThemeType::Text));
            painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::Text));
        }
        if (action && action->getCukeIcon() != IconType::None && !opt->icon.isNull()) {
            QFont font("Cuke");
            font.setPixelSize(pixelMetric(PM_SmallIconSize, opt, widget));
            painter->setFont(font);
            painter->drawText(opt->rect, Qt::AlignCenter, QString(QChar(action->getCukeIcon())));
        } else if (!opt->icon.isNull())
            opt->icon.paint(painter, opt->rect, Qt::AlignCenter);
        else
            painter->drawText(opt->rect.adjusted(1, 1, -1, -1), Qt::AlignCenter, opt->text);

        painter->restore();
        return;
    }
    QProxyStyle::drawControl(element, option, painter, widget);
}

void MenuBarStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

int MenuBarStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

QSize MenuBarStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const {
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == CT_MenuBarItem) {
        if (const auto opt =
                qstyleoption_cast<const QStyleOptionMenuItem *>(option)) {
            if (const auto menuBar = qobject_cast<const QMenuBar *>(widget)) {
                s.setHeight(menuBar->height());
                // 图标被设置后只有图标是可见的
                if (!opt->icon.isNull())
                    s.setWidth(menuBar->height());
                else
                    s.setWidth(qRound(QFontMetrics(opt->font).horizontalAdvance(opt->text) + menuBar->height() * 0.8));
            }
        }
    }
    return s;
}

CUKE_NAMESPACE_END(pub)