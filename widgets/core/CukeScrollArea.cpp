#include "CukeScrollArea.h"
#include "CukeScrollAreaPrivate.h"
#include "CukeScrollAreaStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
ScrollArea::ScrollArea(QWidget *parent)
    : QScrollArea(parent),
      d_ptr(new ScrollAreaPrivate(this)) {
    setStyle(new ScrollAreaStyle(style()));
}

ScrollArea::~ScrollArea() = default;

CUKE_NAMESPACE_END(pub)