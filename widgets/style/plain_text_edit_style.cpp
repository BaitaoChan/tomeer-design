#include "plain_text_edit_style.h"

TOMEER_NAMESPACE_BEGIN()
PlainTextEditStyle::PlainTextEditStyle(QStyle *style)
    : QProxyStyle(style) {
}

PlainTextEditStyle::~PlainTextEditStyle() = default;

TOMEER_NAMESPACE_END