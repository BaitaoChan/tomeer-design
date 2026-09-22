#include "combo_box_private.h"
#include "combo_box.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(ComboBoxPrivate, bool, IsPopup)
ComboBoxPrivate::ComboBoxPrivate(ComboBox *q)
    : QObject(q),
      q_ptr(q) {
}

ComboBoxPrivate::~ComboBoxPrivate() = default;

TOMEER_NAMESPACE_END
