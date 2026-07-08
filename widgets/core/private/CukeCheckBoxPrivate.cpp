#include "CukeCheckBoxPrivate.h"
#include "CukeCheckBox.h"

CUKE_NAMESPACE_BEGIN(pub)
CheckBoxPrivate::CheckBoxPrivate(CheckBox *q)
    : QObject(q),
      q_ptr(q) {
}

CheckBoxPrivate::~CheckBoxPrivate() = default;

void CheckBoxPrivate::onToggled(const bool checked) {
    Q_Q(CheckBox);
    _checkAnim->stop();
    _checkAnim->setStartValue(q->_pCheckProgress);
    _checkAnim->setEndValue(checked ? 1.0 : 0.0);
    _checkAnim->start();
}

CUKE_NAMESPACE_END(pub)