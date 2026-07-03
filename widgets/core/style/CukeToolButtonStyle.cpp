#include <QStyleoption>
#include <QPainter>
#include <QPainterPath>

#include "CukeToolButtonStyle.h"
#include "CukeToolButton.h"
#include "CukeToolBar.h"
#include "CukePainter.h"
#include "CukeIcon.h"

#define CUKE_ARROW_DRAW_MODE 1
CUKE_NAMESPACE_BEGIN(pub)
CukeToolButtonStyle::CukeToolButtonStyle(QStyle *style)
    : QProxyStyle(style) {
}

CukeToolButtonStyle::~CukeToolButtonStyle() = default;

void CukeToolButtonStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto toolButton = qobject_cast<const CukeToolButton *>(widget);
    const auto opt = qstyleoption_cast<const QStyleOptionToolButton *>(option);
    if (element == PE_PanelButtonTool) {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        // 背景
        if (option->state & State_Sunken)
            painter->setBrush(CUKE_THEME->getThemeColor(CukeThemeType::PressAlpha));
        else if (option->state & State_MouseOver)
            painter->setBrush(CUKE_THEME->getThemeColor(CukeThemeType::HoverAlpha));
        CUKE_PAINTER->drawRoundedRect(widget->rect(), painter, toolButton->getBorderRadius(), toolButton->getBorderRadius(), CukeGeometryType::All);
        painter->restore();
        return;
    }
    if (element == PE_IndicatorArrowDown) {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        painter->setPen(CUKE_THEME->getThemeColor(CukeThemeType::Text));
        painter->setBrush(CUKE_THEME->getThemeColor(CukeThemeType::Text));
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
        painter->drawText(rect, Qt::AlignCenter, QString(QChar(CukeIconType::ChevronDown)));
#elif CUKE_ARROW_DRAW_MODE == 1
        QPainterPath path;
        QTransform transform;
        path.addText(QPointF(0, 0), font,
                      QString(QChar(CukeIconType::ChevronDown)));
        transform.translate(center.x(), center.y());
        transform.rotate(toolButton->getRotateAngle());
        transform.translate(-path.boundingRect().center().x(), -path.boundingRect().center().y());
        painter->setPen(Qt::NoPen);
        painter->setBrush(CUKE_THEME->getThemeColor(CukeThemeType::Text));
        painter->setTransform(transform, true);
        painter->drawPath(path);

#elif CUKE_ARROW_DRAW_MODE == 2
        painter->translate(center);
        painter->rotate(toolButton->getRotateAngle());
        painter->translate(-center);
        CUKE_PAINTER->drawIcon(center, painter,
                               QIcon(CUKE_ICON->getCukeIcon(CukeIconType::ChevronDown,
                                                            CUKE_THEME->getThemeColor(CukeThemeType::Text), 64)),
                               QSize(QFontMetrics(opt->font).height(), QFontMetrics(opt->font).height()));
#endif
        painter->restore();
        return;
    }
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void CukeToolButtonStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto toolButton = qobject_cast<const CukeToolButton *>(widget);

    if (element == CE_ToolButtonLabel) {
        const auto opt = qstyleoption_cast<const QStyleOptionToolButton *>(option);
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        painter->setPen(CUKE_THEME->getThemeColor(CukeThemeType::Text));
        painter->setBrush(CUKE_THEME->getThemeColor(CukeThemeType::Text));
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

            if (toolButton->getIconType() != CukeIconType::None) {
                painter->save();
                QFont font("Cuke");
                font.setPixelSize(qRound(opt->iconSize.height() * scale));
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(toolButton->getIconType())));
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

            if (toolButton->getIconType() != CukeIconType::None) {
                painter->save();
                QFont font("Cuke");
                font.setPixelSize(qRound(opt->iconSize.height() * scale));
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(toolButton->getIconType())));
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

            if (toolButton->getIconType() != CukeIconType::None) {
                painter->save();
                QFont font("Cuke");
                font.setPixelSize(qRound(opt->iconSize.height() * scale));
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(toolButton->getIconType())));
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

void CukeToolButtonStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

QSize CukeToolButtonStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const {
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

CUKE_NAMESPACE_END(pub)