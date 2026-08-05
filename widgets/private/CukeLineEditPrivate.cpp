#include "CukeLineEditPrivate.h"
#include "CukeLineEdit.h"

CUKE_NAMESPACE_BEGIN()
LineEditPrivate::LineEditPrivate(LineEdit *q)
    : QObject(q),
      q_ptr(q) {
}

LineEditPrivate::~LineEditPrivate() = default;

CUKE_NAMESPACE_END