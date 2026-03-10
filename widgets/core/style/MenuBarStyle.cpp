#include "MenuBarStyle.h"

CUKE_BEGIN_NAMESPACE(widget)
MenuBarStyle::MenuBarStyle(QStyle *style)
    : ContextMixin(style) {
}

MenuBarStyle::~MenuBarStyle() = default;

CUKE_END_NAMESPACE(widget)