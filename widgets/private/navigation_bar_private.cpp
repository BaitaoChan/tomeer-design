#include "navigation_bar_private.h"

#include "navigation_bar.h"
#include "navigation_bar_view.h"

TOMEER_NAMESPACE_BEGIN()

NavigationBarPrivate::NavigationBarPrivate(NavigationBar *q)
    : QObject(q),
      q_ptr(q) {
}

NavigationBarPrivate::~NavigationBarPrivate() = default;

TOMEER_NAMESPACE_END