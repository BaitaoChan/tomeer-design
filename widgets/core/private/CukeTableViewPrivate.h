#ifndef CUKETABLEVIEWPRIVATE_H
#define CUKETABLEVIEWPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeTableView;
class CukeTableViewPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeTableView)
public:
    explicit CukeTableViewPrivate(CukeTableView *q);
    ~CukeTableViewPrivate() override;
};
CUKE_NAMESPACE_END(pub)


#endif // CUKETABLEVIEWPRIVATE_H
