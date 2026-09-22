#include "check_box_style.h"

#include "check_box.h"

TOMEER_NAMESPACE_BEGIN()
CheckBoxStyle::CheckBoxStyle(QStyle *style)
    : QProxyStyle(style) {
}

CheckBoxStyle::~CheckBoxStyle() = default;

void CheckBoxStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto checkBox = qobject_cast<const CheckBox *>(widget);
    if (element == CE_CheckBox) {
    }
    QProxyStyle::drawControl(element, option, painter, widget);
}

TOMEER_NAMESPACE_END
