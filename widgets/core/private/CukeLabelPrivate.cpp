#include "CukeLabelPrivate.h"
#include "CukeLabel.h"

CUKE_NAMESPACE_BEGIN(pub)
LabelPrivate::LabelPrivate(Label *q)
    : QObject(q),
      q_ptr(q) {
}

LabelPrivate::~LabelPrivate() = default;

CUKE_NAMESPACE_END(pub)