#include "MenuBar.h"
#include "MenuBarPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
MenuBar::MenuBar(QWidget *parent)
    : ContextMixin(parent),
      d_ptr(new MenuBarPrivate(this)) {
}

MenuBar::~MenuBar() = default;

CUKE_END_NAMESPACE(widget)