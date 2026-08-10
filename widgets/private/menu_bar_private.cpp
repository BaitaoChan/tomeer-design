#include "menu_bar_private.h"
#include "menu_bar.h"

TOMEER_NAMESPACE_BEGIN()
MenuBarPrivate::MenuBarPrivate(MenuBar *q)
    : QObject(q),
      q_ptr(q) {
}

MenuBarPrivate::~MenuBarPrivate() = default;

TOMEER_NAMESPACE_END