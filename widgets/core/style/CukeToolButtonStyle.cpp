#include <QStyleoption>
#include <QPainter>
#include <QPainterPath>

#include "CukeToolButtonStyle.h"
#include "CukeToolButton.h"
#include "CukeToolBar.h"
#include "CukePainter.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeToolButtonStyle::CukeToolButtonStyle(QStyle *style)
    : QProxyStyle(style) {
}

CukeToolButtonStyle::~CukeToolButtonStyle() = default;

void CukeToolButtonStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto toolButton = qobject_cast<const CukeToolButton *>(widget);
    if (element == PE_PanelButtonTool) {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        // 背景
        if (option->state & State_Sunken)
            painter->setBrush(cTheme->getThemeColor(toolButton->getThemeMode(), CukeThemeType::PressAlpha));
        else if (option->state & State_MouseOver)
            painter->setBrush(cTheme->getThemeColor(toolButton->getThemeMode(), CukeThemeType::HoverAlpha));
        cPainter->drawRoundedRect(widget->rect(), painter, toolButton->getBorderRadius(), toolButton->getBorderRadius(), CukeGeometryType::All);
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
        painter->setPen(cTheme->getThemeColor(toolButton->getThemeMode(), CukeThemeType::Text));
        painter->setBrush(cTheme->getThemeColor(toolButton->getThemeMode(), CukeThemeType::Text));
        // 文字图标绘制
        constexpr int spacing = 4;
        constexpr qreal scale = 1.0;
        if (opt->toolButtonStyle == Qt::ToolButtonTextOnly) {
            painter->drawText(opt->rect.adjusted(1, 1, -1, 0), Qt::AlignCenter, opt->text);
        }
        if (opt->toolButtonStyle == Qt::ToolButtonIconOnly) {
            QPoint center = opt->rect.center() - QPoint(opt->iconSize.width() / 2, opt->iconSize.height() / 2);
            QRect iRect(center, opt->iconSize);

            if (toolButton->getIconType() != CukeIconType::None) {
                painter->save();
                QFont font("Cuke");
                font.setPixelSize(qRound(opt->iconSize.height() * scale));
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(toolButton->getIconType())));
                painter->restore();
            }
            else
                opt->icon.paint(painter, iRect, Qt::AlignCenter);
        }
        if (opt->toolButtonStyle == Qt::ToolButtonTextBesideIcon) {
            QSize tSize = QFontMetrics(painter->font()).size(Qt::TextSingleLine, opt->text), iSize = opt->iconSize;

            int _width = iSize.width() + spacing + tSize.width();
            int _height = tSize.height();

            QRect _rect(opt->rect.center().x() - _width / 2, opt->rect.center().y() - _height / 2, _width,
                        _height);
            QRect iRect(_rect.left(), _rect.center().y() - iSize.height() / 2, iSize.width(),
                        iSize.height());
            QRect tRect(iRect.right() + spacing, _rect.top(), tSize.width(), _rect.height());

            if (toolButton->getIconType() != CukeIconType::None) {
                painter->save();
                QFont font("Cuke");
                font.setPixelSize(qRound(opt->iconSize.height() * scale));
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(toolButton->getIconType())));
                painter->restore();
            }
            else
                opt->icon.paint(painter, iRect, Qt::AlignCenter);
            painter->drawText(tRect, Qt::AlignVCenter | Qt::AlignLeft, opt->text);
        }
        if (opt->toolButtonStyle == Qt::ToolButtonTextUnderIcon) {
            QSize tSize = QFontMetrics(painter->font()).size(Qt::TextSingleLine, opt->text), iSize = opt->iconSize;

            int _width = tSize.width();
            int _height = iSize.height() + spacing + tSize.height();

            QRect _rect(opt->rect.center().x() - _width / 2, opt->rect.center().y() - _height / 2, _width,
                        _height);
            QRect iRect(_rect.center().x() - iSize.width() / 2, _rect.top(), iSize.width(),
                        iSize.height());
            QRect tRect(_rect.left(), iRect.bottom() + spacing, _width, tSize.height());

            if (toolButton->getIconType() != CukeIconType::None) {
                painter->save();
                QFont font("Cuke");
                font.setPixelSize(qRound(opt->iconSize.height() * scale));
                painter->setFont(font);
                painter->drawText(iRect, Qt::AlignCenter, QString(QChar(toolButton->getIconType())));
                painter->restore();
            }
            else
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

CUKE_NAMESPACE_END(pub)