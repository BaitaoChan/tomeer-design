#include "CukeLineEditPrivate.h"
#include "CukeLineEdit.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeLineEditPrivate::CukeLineEditPrivate(CukeLineEdit *q)
    : QObject(q),
      q_ptr(q) {
}

CukeLineEditPrivate::~CukeLineEditPrivate() = default;

void CukeLineEditPrivate::onLineAnimFinished() {
    Q_Q(CukeLineEdit);
    if (!_isFocused) {
        _hasFocusVisible = false;
        q->update();
    }
}

CUKE_NAMESPACE_END(pub)