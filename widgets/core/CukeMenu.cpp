#include "CukeMenu.h"
#include "CukeMenuStyle.h"
#include "CukeMenuPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeMenu::CukeMenu(QWidget *parent)
    : QMenu(parent),
      d_ptr(new CukeMenuPrivate(this)) {
    Q_D(CukeMenu);
    // 确保应用基本样式
    ensurePolished();
    setStyle(new CukeMenuStyle(style()));
}

CukeMenu::CukeMenu(const QString &title, QWidget *parent)
    : CukeMenu(parent) {
    setTitle(title);
}

CukeMenu::~CukeMenu() = default;
CUKE_NAMESPACE_END(pub)