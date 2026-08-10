#include "menu_private.h"
#include "menu.h"

TOMEER_NAMESPACE_BEGIN()
MenuPrivate::MenuPrivate(Menu *q)
    : QObject(q),
      q_ptr(q) {
}

MenuPrivate::~MenuPrivate() = default;

TOMEER_NAMESPACE_END