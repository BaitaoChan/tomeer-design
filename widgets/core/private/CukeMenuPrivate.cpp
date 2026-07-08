#include "CukeMenuPrivate.h"
#include "CukeMenu.h"

CUKE_NAMESPACE_BEGIN(pub)
MenuPrivate::MenuPrivate(Menu *q)
    : QObject(q),
      q_ptr(q) {
}

MenuPrivate::~MenuPrivate() = default;

CUKE_NAMESPACE_END(pub)