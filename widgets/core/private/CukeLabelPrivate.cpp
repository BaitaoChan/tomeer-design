#include "CukeLabelPrivate.h"
#include "CukeLabel.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeLabelPrivate::CukeLabelPrivate(CukeLabel *q)
    : QObject(q),
      q_ptr(q) {
}

CukeLabelPrivate::~CukeLabelPrivate() = default;

CUKE_NAMESPACE_END(widget)
