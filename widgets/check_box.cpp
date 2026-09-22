#include "check_box.h"
#include "check_box_private.h"

#include "check_box_style.h"

TOMEER_NAMESPACE_BEGIN()
CheckBox::CheckBox(QWidget *parent)
    : QCheckBox(parent),
      d_ptr(new CheckBoxPrivate(this)) {
    setStyle(new CheckBoxStyle(style()));
}

CheckBox::~CheckBox() = default;

TOMEER_NAMESPACE_END
