#include "navigation_bar_view_private.h"

#include "navigation_bar_view.h"

TOMEER_NAMESPACE_BEGIN()

NavigationBarViewPrivate::NavigationBarViewPrivate(NavigationBarView *q)
    : QObject(q),
      q_ptr(q) {
}

NavigationBarViewPrivate::~NavigationBarViewPrivate() = default;

TOMEER_NAMESPACE_END