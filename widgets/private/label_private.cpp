#include "label_private.h"
#include "label.h"

TOMEER_NAMESPACE_BEGIN()
LabelPrivate::LabelPrivate(Label *q)
    : QObject(q),
      q_ptr(q) {
}

LabelPrivate::~LabelPrivate() = default;

TOMEER_NAMESPACE_END
