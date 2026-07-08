#include "CukeLineEditPrivate.h"
#include "CukeLineEdit.h"

CUKE_NAMESPACE_BEGIN(pub)
LineEditPrivate::LineEditPrivate(LineEdit *q)
    : QObject(q),
      q_ptr(q) {
}

LineEditPrivate::~LineEditPrivate() = default;

void LineEditPrivate::onLineAnimFinished() {
    Q_Q(LineEdit);
    if (!_isFocused) {
        _hasFocusVisible = false;
        q->update();
    }
}

CUKE_NAMESPACE_END(pub)