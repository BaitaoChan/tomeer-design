#include "CukeToolButton.h"
#include "CukeToolButtonPrivate.h"
#include "CukeToolButtonStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeToolButton::CukeToolButton(QWidget *parent)
    : CukeContextMixin(parent),
      d_ptr(new CukeToolButtonPrivate(this)) {
    setStyle(new CukeToolButtonStyle());
}

CukeToolButton::~CukeToolButton() = default;

CUKE_NAMESPACE_END(pub)