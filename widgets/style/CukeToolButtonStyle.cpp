#include <QStyleoption>
#include <QPainter>
#include <QPainterPath>

#include "CukeToolButtonStyle.h"
#include "CukeToolButton.h"
#include "CukeToolBar.h"
#include "CukePainter.h"
#include "CukeIcon.h"
#include "CukeAction.h"

#define CUKE_ARROW_DRAW_MODE 1
CUKE_NAMESPACE_BEGIN()
ToolButtonStyle::ToolButtonStyle(QStyle *style)
    : QProxyStyle(style) {
}

ToolButtonStyle::~ToolButtonStyle() = default;

void ToolButtonStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto toolButton = qobject_cast<const ToolButton *>(widget);
    const auto opt = qstyleoption_cast<const QStyleOptionToolButton *>(option);
    if (element == PE_PanelButtonTool) {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        // 背景
        if (!(option->state & State_Enabled) && option->state & State_On)
            painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::Disable));
        else if (option->state & State_Enabled && option->state & State_Sunken && !(option->state & State_On))
            painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::PressAlpha));
        else if (option->state & State_Enabled && option->state & State_On)
            painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::CheckAlpha));
        else if (option->state & State_Enabled && option->state & State_MouseOver)
            painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::HoverAlpha));
        CUKE_PAINTER->drawRoundedRect(widget->rect(), painter, toolButton->getBorderRadius(), toolButton->getBorderRadius(), GeometryType::All);
        painter->restore();
        return;
    }
    if (element == PE_IndicatorArrowDown) {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        if (!(option->state & State_Enabled)) {
            painter->setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::TextDisable), 1));
            painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::TextDisable));
        }
        else {
            if (option->state & State_On) {
                painter->setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::Dark, ThemeType::Text), 1));
                painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::Dark, ThemeType::Text));
            } else {
                painter->setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::Text), 1));
                painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::Text));
            }
        }
        constexpr int spacing = 4;
        QFont font("Cuke");
        font.setPixelSize(opt->iconSize.height());
        painter->setFont(font);
        QSize tSize = QFontMetrics(painter->font()).size(Qt::TextSingleLine, opt->text), iSize = opt->iconSize;
        QRectF rect;
        if (opt->toolButtonStyle == Qt::ToolButtonTextOnly)
            rect = toolButton->rect().adjusted(tSize.width() + spacing, 0, 0, 0);
        if (opt->toolButtonStyle == Qt::ToolButtonIconOnly)
            rect = toolButton->rect().adjusted(iSize.width() + spacing, 0, 0, 0);
        if (opt->toolButtonStyle == Qt::ToolButtonTextBesideIcon)
            rect = toolButton->rect().adjusted(iSize.width() + tSize.width() + spacing, 0, 0, 0);
        if (opt->toolButtonStyle == Qt::ToolButtonTextUnderIcon)
            rect = toolButton->rect().adjusted(qMax(iSize.width(), tSize.width()) + spacing, 0, 0, 0);
        QPointF center = rect.center();

#if CUKE_ARROW_DRAW_MODE == 0
        painter->translate(center);
        painter->rotate(toolButton->getRotateAngle());
        painter->translate(-center);
        painter->drawText(rect, Qt::AlignCenter, QString(QChar(IconType::ChevronDown)));
#elif CUKE_ARROW_DRAW_MODE == 1
        QPainterPath path;
        QTransform transform;
        path.addText(QPointF(0, 0), font,
                      QString(QChar(IconType::ChevronDown)));
        transform.translate(center.x(), center.y());
        transform.rotate(toolButton->getRotateAngle());
        transform.translate(-path.boundingRect().center().x(), -path.boundingRect().center().y());
        painter->setPen(Qt::NoPen);
        painter->setTransform(transform, true);
        painter->drawPath(path);

#elif CUKE_ARROW_DRAW_MODE == 2
        painter->translate(center);
        painter->rotate(toolButton->getRotateAngle());
        painter->translate(-center);
        CUKE_PAINTER->drawIcon(center, painter,
                               QIcon(CUKE_ICON->getCukeIcon(IconType::ChevronDown,
                                                            CUKE_THEME->getThemeColor(option->state & State_Enabled ? ThemeType::Text : ThemeType::TextDisable), 64)),
                               QSize(QFontMetrics(opt->font).height(), QFontMetrics(opt->font).height()));
#endif
        painter->restore();
        return;
    }
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void ToolButtonStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto toolButton = qobject_cast<const ToolButton *>(widget);

    if (element == CE_ToolButtonLabel) {
        const auto opt = qstyleoption_cast<const QStyleOptionToolButton *>(option);
        const auto action = qobject_cast<const Action *>(toolButton->defaultAction());

        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        if (!(option->state & State_Enabled))
            painter->setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::TextDisable), 1));
        else {
            if (option->state & State_On)
                painter->setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::Dark, ThemeType::Text), 1));
            else
                painter->setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::Text), 1));
        }
        // 文字图标绘制
        constexpr int spacing = 4;
        constexpr qreal scale = 1.0;
        // 调整 Arrow 区域
        QRect rect;
        if (opt->features & QStyleOptionToolButton::HasMenu)
            rect = opt->rect.adjusted(0, 0, -(spacing + QFontMetrics(opt->font).height()), 0);
        else
            rect = opt->rect;
        if (opt->toolButtonStyle == Qt::ToolButtonTextOnly) {
            painter->drawText(rect, Qt::AlignCenter, opt->text);
        }
        if (opt->toolButtonStyle == Qt::ToolButtonIconOnly) {
            QPoint center = rect.center() - QPoint(opt->iconSize.width() / 2, opt->iconSize.height() / 2);
            QRect iRect(center, opt->iconSize);

            if (action && action->getCukeIcon() != IconType::None) {
                painter->save();
                QFont font("Cuke");
                font.setPixelSize(qRound(opt->iconSize.height() * scale));
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(action->getCukeIcon())));
                painter->restore();
            } else if (toolButton->getCukeIcon() != IconType::None) {
                painter->save();
                QFont font("Cuke");
                font.setPixelSize(qRound(opt->iconSize.height() * scale));
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(toolButton->getCukeIcon())));
                painter->restore();
            } else
                opt->icon.paint(painter, iRect, Qt::AlignCenter);
        }
        if (opt->toolButtonStyle == Qt::ToolButtonTextBesideIcon) {
            QSize tSize = QFontMetrics(painter->font()).size(Qt::TextSingleLine, opt->text), iSize = opt->iconSize;

            int _width = iSize.width() + spacing + tSize.width();
            int _height = tSize.height();

            QRect lRect(rect.center().x() - _width / 2, rect.center().y() - _height / 2, _width,
                         _height);
            QRect iRect(lRect.left(), lRect.center().y() - iSize.height() / 2, iSize.width(),
                         iSize.height());
            QRect tRect(iRect.right() + spacing, lRect.top(), tSize.width(), lRect.height());


            if (action && action->getCukeIcon() != IconType::None) {
                painter->save();
                QFont font("Cuke");
                font.setPixelSize(qRound(opt->iconSize.height() * scale));
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(action->getCukeIcon())));
                painter->restore();
            } else if (toolButton->getCukeIcon() != IconType::None) {
                painter->save();
                QFont font("Cuke");
                font.setPixelSize(qRound(opt->iconSize.height() * scale));
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(toolButton->getCukeIcon())));
                painter->restore();
            } else
                opt->icon.paint(painter, iRect, Qt::AlignCenter);
            painter->drawText(tRect, Qt::AlignVCenter | Qt::AlignLeft, opt->text);
        }
        if (opt->toolButtonStyle == Qt::ToolButtonTextUnderIcon) {
            QSize tSize = QFontMetrics(painter->font()).size(Qt::TextSingleLine, opt->text), iSize = opt->iconSize;

            int _width = tSize.width();
            int _height = iSize.height() + spacing + tSize.height();

            QRect lRect(rect.center().x() - _width / 2, rect.center().y() - _height / 2, _width,
                         _height);
            QRect iRect(lRect.center().x() - iSize.width() / 2, lRect.top(), iSize.width(),
                         iSize.height());
            QRect tRect(lRect.left(), iRect.bottom() + spacing, _width, tSize.height());

            if (action && action->getCukeIcon() != IconType::None) {
                painter->save();
                QFont font("Cuke");
                font.setPixelSize(qRound(opt->iconSize.height() * scale));
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(action->getCukeIcon())));
                painter->restore();
            } else if (toolButton->getCukeIcon() != IconType::None) {
                painter->save();
                QFont font("Cuke");
                font.setPixelSize(qRound(opt->iconSize.height() * scale));
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(toolButton->getCukeIcon())));
                painter->restore();
            } else
                opt->icon.paint(painter, iRect, Qt::AlignCenter);
            painter->drawText(tRect, Qt::AlignHCenter | Qt::AlignTop, opt->text);
        }
        painter->restore();
        return;
    }
    QProxyStyle::drawControl(element, option, painter, widget);
}

void ToolButtonStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

QSize ToolButtonStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const {
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    constexpr int spacing = 4;

    if (type == CT_ToolButton) {
        const auto opt = qstyleoption_cast<const QStyleOptionToolButton *>(option);
        if (opt->features & QStyleOptionToolButton::HasMenu) {
            s.rwidth() += spacing;
            s.rwidth() += QFontMetrics(opt->font).height();
        }
    }
    return s;
}

CUKE_NAMESPACE_END