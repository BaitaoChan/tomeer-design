#include "CukeComboBoxPrivate.h"
#include "CukeComboBox.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeComboBoxPrivate::CukeComboBoxPrivate(CukeComboBox *q)
    : QObject(q),
      q_ptr(q) {
}

CukeComboBoxPrivate::~CukeComboBoxPrivate() = default;

CUKE_NAMESPACE_END(widget)