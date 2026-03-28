#include <QPropertyAnimation>

#include "CukeToolButtonPrivate.h"
#include "CukeToolButton.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeToolButtonPrivate::CukeToolButtonPrivate(CukeToolButton *q)
    : QObject(q), q_ptr(q) {
}

CukeToolButtonPrivate::~CukeToolButtonPrivate() = default;

void CukeToolButtonPrivate::onHoverChanged() {
    Q_Q(CukeToolButton);
    if (q->_pHover) {
        _bgAnim->stop();
        _bgAnim->setStartValue(*_bgColorFrom);
        _bgAnim->setEndValue(*_bgColorTo);
        _bgAnim->start();
    } else {
        _bgAnim->stop();
        _bgAnim->setStartValue(*_bgColorTo);
        _bgAnim->setEndValue(*_bgColorFrom);
        _bgAnim->start();
    }
}

CUKE_NAMESPACE_END(pub)