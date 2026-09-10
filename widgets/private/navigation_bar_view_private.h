#ifndef NAVIGATION_BAR_VIEW_PRIVATE_H
#define NAVIGATION_BAR_VIEW_PRIVATE_H

#include <QModelIndex>

#include "property.h"

class QPropertyAnimation;
TOMEER_NAMESPACE_BEGIN()
class NavigationBarView;
class NavigationBarViewPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(NavigationBarView)
public:
    explicit NavigationBarViewPrivate(NavigationBarView *q);
    ~NavigationBarViewPrivate() override;

private:
    QPropertyAnimation *_rotateAnim = nullptr;
    QModelIndex _togglingIndex;
    QModelIndex _pressedIndex;
};
TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_VIEW_PRIVATE_H