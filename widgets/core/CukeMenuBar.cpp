#include "CukeMenuBar.h"
#include "CukeMenuBarStyle.h"
#include "CukeMenuBarPrivate.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeMenuBar::CukeMenuBar(QWidget *parent)
    : CukeContextMixin(parent),
      d_ptr(new CukeMenuBarPrivate(this)) {
    setStyle(new CukeMenuBarStyle(style()));
}

CukeMenuBar::~CukeMenuBar() = default;

CUKE_NAMESPACE_END(widget)