#include "CukeFloatLineEditPrivate.h"
#include "CukeFloatLineEdit.h"

CUKE_NAMESPACE_BEGIN(lab)
FloatLineEditPrivate::FloatLineEditPrivate(FloatLineEdit *q)
    : QObject(q),
      q_ptr(q) {
}

FloatLineEditPrivate::~FloatLineEditPrivate() = default;

CUKE_NAMESPACE_END(lab)