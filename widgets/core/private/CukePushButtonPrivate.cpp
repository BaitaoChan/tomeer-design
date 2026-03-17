#include "CukePushButtonPrivate.h"
#include "CukePushButton.h"

CUKE_NAMESPACE_BEGIN(widget)
CukePushButtonPrivate::CukePushButtonPrivate(CukePushButton *q)
    : QObject(q),
      q_ptr(q) {
}

CukePushButtonPrivate::~CukePushButtonPrivate() = default;

CUKE_NAMESPACE_END(widget)