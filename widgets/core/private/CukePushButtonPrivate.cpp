#include "CukePushButtonPrivate.h"
#include "CukePushButton.h"

CUKE_NAMESPACE_BEGIN(pub)
CukePushButtonPrivate::CukePushButtonPrivate(CukePushButton *q)
    : QObject(q),
      q_ptr(q) {
}

CukePushButtonPrivate::~CukePushButtonPrivate() = default;

CUKE_NAMESPACE_END(pub)