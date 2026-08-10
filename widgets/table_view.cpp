#include "table_view.h"
#include "table_item_delegate.h"
#include "table_view_style.h"
#include "table_view_private.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(TableView, ThemeType::ThemeMode, ThemeMode)
TableView::TableView(QWidget *parent)
    : QTableView(parent),
      d_ptr(new TableViewPrivate(this)) {
    Q_D(TableView);
    setStyle(new TableViewStyle(style()));
    setItemDelegate(new TableItemDelegate(this));

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
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &TableView::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

TableView::~TableView() = default;

void TableView::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(TableView);
    setThemeMode(mode);
    update();
}

TOMEER_NAMESPACE_END