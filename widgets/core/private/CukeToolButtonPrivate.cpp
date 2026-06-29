#include <QPropertyAnimation>

#include "CukeToolButtonPrivate.h"
#include "CukeToolButton.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeToolButtonPrivate::CukeToolButtonPrivate(CukeToolButton *q)
    : QObject(q), q_ptr(q) {
}

CukeToolButtonPrivate::~CukeToolButtonPrivate() = default;

void CukeToolButtonPrivate::onMenuShow() {
    Q_Q(CukeToolButton);
    _rotateAnim->stop();
    _rotateAnim->setStartValue(q->getRotateAngle());
    _rotateAnim->setEndValue(-180);
    _rotateAnim->start();
}

void CukeToolButtonPrivate::onMenuHide() {
    Q_Q(CukeToolButton);
    _rotateAnim->stop();
    _rotateAnim->setStartValue(q->getRotateAngle());
    _rotateAnim->setEndValue(0);
    _rotateAnim->start();
}

CUKE_NAMESPACE_END(pub)