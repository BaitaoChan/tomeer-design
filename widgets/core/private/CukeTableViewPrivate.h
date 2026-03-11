#ifndef CUKETABLEVIEWPRIVATE_H
#define CUKETABLEVIEWPRIVATE_H
#include "CukeProperty.h"

CUKE_BEGIN_NAMESPACE(widget)
class CukeTableView;
class CukeTableViewPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeTableView)
public:
    explicit CukeTableViewPrivate(CukeTableView *q);
    ~CukeTableViewPrivate() override;
};
CUKE_END_NAMESPACE(widget)


#endif // CUKETABLEVIEWPRIVATE_H
