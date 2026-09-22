#include <QPainter>
#include <QStyleOption>

#include "line_edit_style.h"
#include "line_edit.h"
#include "theme.h"

TOMEER_NAMESPACE_BEGIN()
LineEditStyle::LineEditStyle(QStyle *style)
    : QProxyStyle(style) {
}

LineEditStyle::~LineEditStyle() = default;

void LineEditStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto lineEdit = qobject_cast<const LineEdit *>(widget);
    if (element == PE_PanelLineEdit) {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        painter->setPen(TOMEER_THEME->getThemeColor(ThemeType::BorderAlpha));
        painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::LineEdit));
        painter->drawRoundedRect(option->rect.adjusted(1, 1, -1, -1), lineEdit->getBorderRadius(), lineEdit->getBorderRadius());

        painter->restore();
        return;
    }
    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void LineEditStyle::polish(QWidget *widget) {
    QProxyStyle::polish(widget);
    const auto lineEdit = qobject_cast<LineEdit *>(widget);

    QPalette pal = lineEdit->palette();
    pal.setColor(QPalette::Text, TOMEER_THEME->getThemeColor(lineEdit->getThemeMode(), ThemeType::Text));
    pal.setColor(QPalette::PlaceholderText, TOMEER_THEME->getThemeColor(lineEdit->getThemeMode(), ThemeType::TextDisable));
    lineEdit->setPalette(pal);
}

TOMEER_NAMESPACE_END
