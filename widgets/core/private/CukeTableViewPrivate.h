#ifndef CUKETABLEVIEWPRIVATE_H
#define CUKETABLEVIEWPRIVATE_H
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(widget)
class CukeTableView;
class CukeTableViewPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeTableView)
public:
    explicit CukeTableViewPrivate(CukeTableView *q);
    ~CukeTableViewPrivate() override;
};
CUKE_NAMESPACE_END(widget)


#endif // CUKETABLEVIEWPRIVATE_H
