#include <QPainter>
#include <QStyleOption>

#include "plain_text_edit_style.h"
#include "plain_text_edit.h"
#include "theme.h"

TOMEER_NAMESPACE_BEGIN()
PlainTextEditStyle::PlainTextEditStyle(QStyle *style)
    : QProxyStyle(style) {
}

PlainTextEditStyle::~PlainTextEditStyle() = default;

void PlainTextEditStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void PlainTextEditStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto plainTextEdit = qobject_cast<const PlainTextEdit *>(widget);
    if (element == CE_ShapedFrame && plainTextEdit) {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        painter->setPen(TOMEER_THEME->getThemeColor(ThemeType::BorderAlpha));
        painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::LineEdit));
        painter->drawRoundedRect(option->rect.adjusted(1, 1, -1, -1), plainTextEdit->getBorderRadius(), plainTextEdit->getBorderRadius());

        const QRectF lineRect(option->rect.left() + 4,
                              option->rect.bottom() - 4,
                              qMax(0, option->rect.width() - 8),
                              2);
        painter->setPen(Qt::NoPen);
        painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::Pattern));
        painter->drawRoundedRect(lineRect, 2, 2);

        const qreal lineHalfWidth = qMin<qreal>(plainTextEdit->getLineHalfWidth(), lineRect.width() / 2.0);
        painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::Check));
        painter->drawRoundedRect(QRectF(lineRect.center().x() - lineHalfWidth,
                                        lineRect.top(),
                                        lineHalfWidth * 2,
                                        3),
                                 2,
                                 2);

        painter->restore();
        return;
    }
    QProxyStyle::drawControl(element, option, painter, widget);
}

void PlainTextEditStyle::polish(QWidget *widget) {
    QProxyStyle::polish(widget);
    const auto plainTextEdit = qobject_cast<PlainTextEdit *>(widget);
    if (!plainTextEdit)
        return;

    QPalette pal = plainTextEdit->palette();
    pal.setColor(QPalette::Base, TOMEER_THEME->getThemeColor(plainTextEdit->getThemeMode(), ThemeType::LineEdit));
    pal.setColor(QPalette::Text, TOMEER_THEME->getThemeColor(plainTextEdit->getThemeMode(), ThemeType::Text));
    pal.setColor(QPalette::PlaceholderText, TOMEER_THEME->getThemeColor(plainTextEdit->getThemeMode(), ThemeType::TextDisable));
    plainTextEdit->setPalette(pal);
    plainTextEdit->viewport()->setAutoFillBackground(false);
}

TOMEER_NAMESPACE_END