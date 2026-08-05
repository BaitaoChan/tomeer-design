#include "CukeComboBoxPrivate.h"
#include "CukeComboBox.h"

CUKE_NAMESPACE_BEGIN()
CUKE_Q_PROPERTY_IMPL(ComboBoxPrivate, bool, IsPopup)
ComboBoxPrivate::ComboBoxPrivate(ComboBox *q)
    : QObject(q),
      q_ptr(q) {
}

ComboBoxPrivate::~ComboBoxPrivate() = default;

CUKE_NAMESPACE_END