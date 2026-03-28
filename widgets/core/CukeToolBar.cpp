#include "CukeToolBar.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeToolBar::CukeToolBar(QWidget *parent)
    : QToolBar(parent),
      CukeScope(this) {
}

CukeToolBar::~CukeToolBar() = default;

CUKE_NAMESPACE_END(pub)