#include "CukeTableViewPrivate.h"
#include "CukeTableView.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeTableViewPrivate::CukeTableViewPrivate(CukeTableView *q)
    : QObject(q),
      q_ptr(q) {
}

CukeTableViewPrivate::~CukeTableViewPrivate() = default;

CUKE_NAMESPACE_END(widget)
