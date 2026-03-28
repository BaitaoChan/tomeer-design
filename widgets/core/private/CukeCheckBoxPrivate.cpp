#include "CukeCheckBoxPrivate.h"
#include "CukeCheckBox.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeCheckBoxPrivate::CukeCheckBoxPrivate(CukeCheckBox *q)
    : QObject(q),
      q_ptr(q) {
}

CukeCheckBoxPrivate::~CukeCheckBoxPrivate() = default;

void CukeCheckBoxPrivate::onToggled(const bool checked) {
    Q_Q(CukeCheckBox);
    _checkAnim->stop();
    _checkAnim->setStartValue(q->_pCheckProgress);
    _checkAnim->setEndValue(checked ? 1.0 : 0.0);
    _checkAnim->start();
}

CUKE_NAMESPACE_END(pub)