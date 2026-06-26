#include "CukeMenu.h"
#include "CukeMenuStyle.h"
#include "CukeMenuPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeMenu::CukeMenu(QWidget *parent)
    : QMenu(parent),
      d_ptr(new CukeMenuPrivate(this)) {
    Q_D(CukeMenu);
    setStyle(new CukeMenuStyle(style()));
}

CukeMenu::CukeMenu(const QString &title, QWidget *parent)
    : QMenu(title, parent),
      d_ptr(new CukeMenuPrivate(this)) {
    Q_D(CukeMenu);
    setStyle(new CukeMenuStyle(style()));
}

CukeMenu::~CukeMenu() {
    Q_D(CukeMenu);
    delete this->style();
}
CUKE_NAMESPACE_END(pub)