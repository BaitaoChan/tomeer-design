#include "CukeLineEditPrivate.h"
#include "CukeLineEdit.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeLineEditPrivate::CukeLineEditPrivate(CukeLineEdit *q)
    : QObject(q),
      q_ptr(q) {
}

CukeLineEditPrivate::~CukeLineEditPrivate() = default;

CUKE_NAMESPACE_END(pub)