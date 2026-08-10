#include <QStyleoption>
#include <QPainter>
#include <QPainterPath>

#include "app_bar_button_style.h"
#include "app_bar_button.h"
#include "painter.h"

TOMEER_NAMESPACE_BEGIN()
AppBarButtonStyle::AppBarButtonStyle(QStyle *style)
    : QProxyStyle(style) {
}

AppBarButtonStyle::~AppBarButtonStyle() = default;

void AppBarButtonStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto appBarButton = qobject_cast<const AppBarButton *>(widget);
    if (element == PE_PanelButtonBevel) {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        // 背景
        if (appBarButton->getBgColorUsedFlag()) {
            if (option->state & State_Sunken || option->state & State_MouseOver)
                painter->setBrush(appBarButton->getBgColor());
        } else {
            if (option->state & State_Sunken)
                painter->setBrush(TOMEER_THEME->getThemeColor(appBarButton->getThemeMode(), ThemeType::PressAlpha));
            else if (option->state & State_MouseOver)
                painter->setBrush(TOMEER_THEME->getThemeColor(appBarButton->getThemeMode(), ThemeType::HoverAlpha));
        }
        TOMEER_PAINTER->drawRoundedRect(option->rect, painter, appBarButton->getBorderRadius(), appBarButton->getBorderRadius(), appBarButton->getSideFlag());
        painter->restore();
        return;
    }
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void AppBarButtonStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto appBarButton = qobject_cast<const AppBarButton *>(widget);
    const auto opt = qstyleoption_cast<const QStyleOptionToolButton *>(option);

    if (element == CE_ToolButtonLabel) {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

        // 关闭图标特殊处理
        if (appBarButton->getIcon() == IconType::Dismiss && appBarButton->getHover()) {
            painter->setPen(TOMEER_THEME->getThemeColor(ThemeType::Dark, ThemeType::Text));
            painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::Dark, ThemeType::Text));
        } else {
            painter->setPen(TOMEER_THEME->getThemeColor(ThemeType::Text));
            painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::Text));
        }

        QRect rect = opt->rect;
        QSize iSize = opt->iconSize;

        QPoint center = rect.center() - QPoint(iSize.width() / 2, iSize.height() / 2);
        QRect iRect(center, iSize);

        if (appBarButton->getIcon() != IconType::None) {
            QFont font("tomeer");
            font.setPixelSize(iSize.height());
            painter->setFont(font);
            painter->drawText(iRect, Qt::AlignCenter, QString(QChar(appBarButton->getIcon())));
        } else {
            opt->icon.paint(painter, iRect, Qt::AlignCenter);
        }

        painter->restore();
        return;
    }

    QProxyStyle::drawControl(element, option, painter, widget);
}

void AppBarButtonStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

int AppBarButtonStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

TOMEER_NAMESPACE_END