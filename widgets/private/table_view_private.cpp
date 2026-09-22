#include "table_view_private.h"
#include "table_view.h"

TOMEER_NAMESPACE_BEGIN()
TableViewPrivate::TableViewPrivate(TableView *q)
    : QObject(q),
      q_ptr(q) {
}

TableViewPrivate::~TableViewPrivate() = default;

TOMEER_NAMESPACE_END
