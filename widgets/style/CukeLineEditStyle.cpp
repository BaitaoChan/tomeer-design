#include <QPainter>
#include <QStyleOption>

#include "CukeLineEditStyle.h"
#include "CukeLineEdit.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN()
LineEditStyle::LineEditStyle(QStyle *style)
    : QProxyStyle(style) {
}

LineEditStyle::~LineEditStyle() = default;

void LineEditStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto lineEdit = qobject_cast<const LineEdit *>(widget);
    if (element == PE_PanelLineEdit) {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        painter->setPen(CUKE_THEME->getThemeColor(ThemeType::BorderAlpha));
        painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::LineEdit));
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
    pal.setColor(QPalette::Text, CUKE_THEME->getThemeColor(lineEdit->getThemeMode(), ThemeType::Text));
    pal.setColor(QPalette::PlaceholderText, CUKE_THEME->getThemeColor(lineEdit->getThemeMode(), ThemeType::TextDisable));
    lineEdit->setPalette(pal);
}

CUKE_NAMESPACE_END