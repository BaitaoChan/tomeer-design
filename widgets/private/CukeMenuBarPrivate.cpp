#include "CukeMenuBarPrivate.h"
#include "CukeMenuBar.h"

CUKE_NAMESPACE_BEGIN()
MenuBarPrivate::MenuBarPrivate(MenuBar *q)
    : QObject(q),
      q_ptr(q) {
}

MenuBarPrivate::~MenuBarPrivate() = default;

CUKE_NAMESPACE_END