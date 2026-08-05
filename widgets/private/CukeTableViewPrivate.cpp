#include "CukeTableViewPrivate.h"
#include "CukeTableView.h"

CUKE_NAMESPACE_BEGIN()
TableViewPrivate::TableViewPrivate(TableView *q)
    : QObject(q),
      q_ptr(q) {
}

TableViewPrivate::~TableViewPrivate() = default;

CUKE_NAMESPACE_END