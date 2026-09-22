#include <QPropertyAnimation>

#include "navigation_bar_view_private.h"
#include "navigation_bar_view.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(NavigationBarViewPrivate, bool, Downward)
NavigationBarViewPrivate::NavigationBarViewPrivate(NavigationBarView *q)
    : QObject(q),
      q_ptr(q) {
}

NavigationBarViewPrivate::~NavigationBarViewPrivate() = default;

void NavigationBarViewPrivate::onExpanded(const QModelIndex &index) {
    Q_Q(NavigationBarView);
    qreal startAngle = 0.0;
    if (_togglingIndex == index) {
        if (_rotateAnim->state() == QAbstractAnimation::Running)
            startAngle = q->getRotateAngle();
    }

    _rotateAnim->stop();
    _togglingIndex = index;
    q->setRotateAngle(startAngle);
    _rotateAnim->setStartValue(startAngle);
    _rotateAnim->setEndValue(180.0);
    _rotateAnim->start();
}

void NavigationBarViewPrivate::onCollapsed(const QModelIndex &index) {
    Q_Q(NavigationBarView);
    qreal startAngle = 180.0;
    if (_togglingIndex == index) {
        if (_rotateAnim->state() == QAbstractAnimation::Running)
            startAngle = q->getRotateAngle();
    }

    _rotateAnim->stop();
    _togglingIndex = index;
    q->setRotateAngle(startAngle);
    _rotateAnim->setStartValue(startAngle);
    _rotateAnim->setEndValue(0.0);
    _rotateAnim->start();
}

QRect NavigationBarViewPrivate::_indicatorRect(const QModelIndex &index) const {
    Q_Q(const NavigationBarView);

    QRect _rect = q->visualRect(index);
    if (_rect.isEmpty())
        return {};

    QRect rect(0, 0, 3, 16);
    rect.moveCenter(_rect.adjusted(4, 2, -4, -2).center());
    rect.moveLeft(_rect.left() + 4);

    return rect;
}

TOMEER_NAMESPACE_END
