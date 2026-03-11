#include "CukeTableView.h"
#include "CukeTableItemDelegate.h"
#include "CukeTableViewStyle.h"
#include "CukeTableViewPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
CukeTableView::CukeTableView(QWidget *parent)
    : CukeContextMixin(parent),
      d_ptr(new CukeTableViewPrivate(this)) {

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
}

CukeTableView::~CukeTableView() = default;

CUKE_END_NAMESPACE(widget)