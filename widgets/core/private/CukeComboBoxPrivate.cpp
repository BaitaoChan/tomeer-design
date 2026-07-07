#include "CukeComboBoxPrivate.h"
#include "CukeComboBox.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeComboBoxPrivate, bool, IsPopup)
CukeComboBoxPrivate::CukeComboBoxPrivate(CukeComboBox *q)
    : QObject(q),
      q_ptr(q) {
}

CukeComboBoxPrivate::~CukeComboBoxPrivate() = default;

CUKE_NAMESPACE_END(pub)