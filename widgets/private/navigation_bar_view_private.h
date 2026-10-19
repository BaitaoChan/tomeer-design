#ifndef NAVIGATION_BAR_VIEW_PRIVATE_H
#define NAVIGATION_BAR_VIEW_PRIVATE_H

#include <QModelIndex>

#include "property.h"

class QVariantAnimation;
class QPropertyAnimation;
TOMEER_NAMESPACE_BEGIN()
class NavigationBarView;
class NavigationBarViewPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(NavigationBarView)
    TOMEER_Q_PROPERTY_DECL(bool, Downward)
public:
    explicit NavigationBarViewPrivate(NavigationBarView *q);
    ~NavigationBarViewPrivate() override;

    Q_SLOT void onExpanded(const QModelIndex &index);
    Q_SLOT void onCollapsed(const QModelIndex &index);
    Q_SLOT void onIsCompactedChanged();

private:
    QRect _indicatorRect(const QModelIndex &index) const;

    QVariantAnimation *_indicatorAnim = nullptr;
    QPropertyAnimation *_rotateAnim = nullptr;

    QModelIndex _togglingIndex;
    QModelIndex _pressedIndex;

    // 指示条动画过程中跟踪前后项
    QPersistentModelIndex _previousIndex;
    QPersistentModelIndex _currentIndex;
};
TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_VIEW_PRIVATE_H
