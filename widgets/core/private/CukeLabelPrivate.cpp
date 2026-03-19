#include "CukeLabelPrivate.h"
#include "CukeLabel.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeLabelPrivate::CukeLabelPrivate(CukeLabel *q)
    : QObject(q),
      q_ptr(q) {
}

CukeLabelPrivate::~CukeLabelPrivate() = default;

CUKE_NAMESPACE_END(pub)
