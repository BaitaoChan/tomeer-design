#include "CukeTableView.h"
#include "CukeTableItemDelegate.h"
#include "CukeTableViewStyle.h"
#include "CukeTableViewPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(TableView, ThemeType::ThemeMode, ThemeMode)
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
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &TableView::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

TableView::~TableView() = default;

void TableView::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(TableView);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)