#include "CukeCheckBoxPrivate.h"
#include "CukeCheckBox.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeCheckBoxPrivate::CukeCheckBoxPrivate(CukeCheckBox *q)
    : QObject(q),
      q_ptr(q) {
}

CukeCheckBoxPrivate::~CukeCheckBoxPrivate() = default;
CUKE_NAMESPACE_END(widget)