#include <QPropertyAnimation>

#include "CukeToolButtonPrivate.h"
#include "CukeToolButton.h"

CUKE_NAMESPACE_BEGIN()
ToolButtonPrivate::ToolButtonPrivate(ToolButton *q)
    : QObject(q), q_ptr(q) {
}

ToolButtonPrivate::~ToolButtonPrivate() = default;

void ToolButtonPrivate::onMenuShow() {
    Q_Q(ToolButton);
    _rotateAnim->stop();
    _rotateAnim->setStartValue(q->getRotateAngle());
    _rotateAnim->setEndValue(-180);
    _rotateAnim->start();
}

void ToolButtonPrivate::onMenuHide() {
    Q_Q(ToolButton);
    _rotateAnim->stop();
    _rotateAnim->setStartValue(q->getRotateAngle());
    _rotateAnim->setEndValue(0);
    _rotateAnim->start();
}

CUKE_NAMESPACE_END