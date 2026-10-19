#include <QPropertyAnimation>
#include <QStyle>

#include "navigation_bar_view_private.h"
#include "navigation_bar_view.h"

#include "tool_tip.h"

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

void NavigationBarViewPrivate::onIsCompactedChanged() {
    Q_Q(NavigationBarView);
    const bool compact = q->getIsCompacted();
    // 展开态跟随样式给出的缩进，收起态归零让各级图标落在同一列
    q->setIndentation(compact ? 0 : q->style()->pixelMetric(QStyle::PM_TreeViewIndentation, nullptr, q));
    if (!compact)
        ToolTip::hideText();
    // 缩进参与项矩形计算，必须重新布局才会生效
    q->doItemsLayout();
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
