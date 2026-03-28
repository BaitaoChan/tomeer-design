#include "CukeMenuBar.h"
#include "CukeMenuBarStyle.h"
#include "CukeMenuBarPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeMenuBar::CukeMenuBar(QWidget *parent)
    : QMenuBar(parent),
      CukeScope(this),
      d_ptr(new CukeMenuBarPrivate(this)) {
    Q_D(CukeMenuBar);
    setStyle(new CukeMenuBarStyle(style()));
}

CukeMenuBar::~CukeMenuBar() = default;

CUKE_NAMESPACE_END(pub)