#include <QPropertyAnimation>

#include "CukeAppBarButtonPrivate.h"
#include "CukeAppBarButton.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeAppBarButtonPrivate::CukeAppBarButtonPrivate(CukeAppBarButton *q)
    : QObject(q),
      q_ptr(q) {
}

CukeAppBarButtonPrivate::~CukeAppBarButtonPrivate() = default;

void CukeAppBarButtonPrivate::onHoverChanged() {
    Q_Q(CukeAppBarButton);
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