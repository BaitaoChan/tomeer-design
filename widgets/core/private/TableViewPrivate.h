#ifndef TABLEVIEWPRIVATE_H
#define TABLEVIEWPRIVATE_H
#include "Property.h"

CUKE_BEGIN_NAMESPACE(widget)
class TableView;
class TableViewPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(TableView)
public:
    explicit TableViewPrivate(TableView *q);
    ~TableViewPrivate() override;
};
CUKE_END_NAMESPACE(widget)


#endif // TABLEVIEWPRIVATE_H
