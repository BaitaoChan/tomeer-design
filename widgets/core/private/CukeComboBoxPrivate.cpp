#include "CukeComboBoxPrivate.h"
#include "CukeComboBox.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeComboBoxPrivate::CukeComboBoxPrivate(CukeComboBox *q)
    : QObject(q),
      q_ptr(q) {
}

CukeComboBoxPrivate::~CukeComboBoxPrivate() = default;

CUKE_NAMESPACE_END(pub)