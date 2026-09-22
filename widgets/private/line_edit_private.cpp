#include "line_edit_private.h"
#include "line_edit.h"

TOMEER_NAMESPACE_BEGIN()
LineEditPrivate::LineEditPrivate(LineEdit *q)
    : QObject(q),
      q_ptr(q) {
}

LineEditPrivate::~LineEditPrivate() = default;

TOMEER_NAMESPACE_END
