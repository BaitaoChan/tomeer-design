#include "CukeFloatLineEditPrivate.h"
#include "CukeFloatLineEdit.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeFloatLineEditPrivate::CukeFloatLineEditPrivate(CukeFloatLineEdit *q)
    : QObject(q),
      q_ptr(q) {
}

CukeFloatLineEditPrivate::~CukeFloatLineEditPrivate() = default;

CUKE_NAMESPACE_END(widget)