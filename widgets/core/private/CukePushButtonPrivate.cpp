#include "CukePushButtonPrivate.h"

#include "CukePushButton.h"

CUKE_NAMESPACE_BEGIN(pub)
PushButtonPrivate::PushButtonPrivate(PushButton *q)
    : QObject(q),
      q_ptr(q) {
}

PushButtonPrivate::~PushButtonPrivate() = default;
CUKE_NAMESPACE_END(pub)
