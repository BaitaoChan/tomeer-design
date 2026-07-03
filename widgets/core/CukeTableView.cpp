#include "CukeTableView.h"
#include "CukeTableItemDelegate.h"
#include "CukeTableViewStyle.h"
#include "CukeTableViewPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeTableView, CukeThemeType::ThemeMode, ThemeMode)
CukeTableView::CukeTableView(QWidget *parent)
    : QTableView(parent),
      d_ptr(new CukeTableViewPrivate(this)) {
    Q_D(CukeTableView);
    setStyle(new CukeTableViewStyle(style()));
    setItemDelegate(new CukeTableItemDelegate(this));

    setStyleSheet(R"(
        QTableView {
            background: transparent;
        }
        QHeaderView {
            background: transparent;
            border: none;
        }
    )");

    setShowGrid(false);
    setAlternatingRowColors(false);
    connect(CUKE_THEME, &CukeTheme::themeModeChanged, this, &CukeTableView::onThemeChanged);
}

CukeTableView::~CukeTableView() = default;

void CukeTableView::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeTableView);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)