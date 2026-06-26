#include "CukeMenu.h"
#include "CukeMenuStyle.h"
#include "CukeMenuPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeMenu::CukeMenu(QWidget *parent)
    : QMenu(parent),
      d_ptr(new CukeMenuPrivate(this)) {
    setStyle(new CukeMenuStyle(style()));
}

CukeMenu::~CukeMenu() = default;
CUKE_NAMESPACE_END(pub)