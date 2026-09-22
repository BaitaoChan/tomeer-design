#include "check_box_private.h"

#include "check_box.h"

TOMEER_NAMESPACE_BEGIN()
CheckBoxPrivate::CheckBoxPrivate(CheckBox *q)
    : QObject(q),
      q_ptr(q) {
}

CheckBoxPrivate::~CheckBoxPrivate() = default;

TOMEER_NAMESPACE_END
