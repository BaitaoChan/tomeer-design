#ifndef CUKETABLEVIEWPRIVATE_H
#define CUKETABLEVIEWPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class TableView;
class TableViewPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(TableView)
public:
    explicit TableViewPrivate(TableView *q);
    ~TableViewPrivate() override;
};
CUKE_NAMESPACE_END(pub)


#endif // CUKETABLEVIEWPRIVATE_H