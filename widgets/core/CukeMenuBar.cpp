#include "CukeMenuBar.h"
#include "CukeMenuBarStyle.h"
#include "CukeMenuBarPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
CukeMenuBar::CukeMenuBar(QWidget *parent)
    : CukeContextMixin(parent),
      d_ptr(new CukeMenuBarPrivate(this)) {
    setStyle(new CukeMenuBarStyle(style()));
}

CukeMenuBar::~CukeMenuBar() = default;

CUKE_END_NAMESPACE(widget)