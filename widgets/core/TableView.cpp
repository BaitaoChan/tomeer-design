#include "TableView.h"
#include "TableItemDelegate.h"
#include "TableViewStyle.h"
#include "TableViewPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
TableView::TableView(QWidget *parent)
    : ContextMixin(parent),
      d_ptr(new TableViewPrivate(this)) {

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
}

TableView::~TableView() = default;

CUKE_END_NAMESPACE(widget)