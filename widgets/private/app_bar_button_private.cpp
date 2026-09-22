#include <QPropertyAnimation>

#include "app_bar_button_private.h"
#include "app_bar_button.h"

TOMEER_NAMESPACE_BEGIN()
AppBarButtonPrivate::AppBarButtonPrivate(AppBarButton *q)
    : QObject(q),
      q_ptr(q) {
}

AppBarButtonPrivate::~AppBarButtonPrivate() = default;

void AppBarButtonPrivate::onHoverChanged() {
    Q_Q(AppBarButton);
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

TOMEER_NAMESPACE_END
