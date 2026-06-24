#include <QPropertyAnimation>

#include "CukeToolButtonPrivate.h"
#include "CukeToolButton.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeToolButtonPrivate::CukeToolButtonPrivate(CukeToolButton *q)
    : QObject(q), q_ptr(q) {
}

CukeToolButtonPrivate::~CukeToolButtonPrivate() = default;

CUKE_NAMESPACE_END(pub)