#ifndef TABLE_VIEW_PRIVATE_H
#define TABLE_VIEW_PRIVATE_H
#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class TableView;
class TableViewPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(TableView)
public:
    explicit TableViewPrivate(TableView *q);
    ~TableViewPrivate() override;
};
TOMEER_NAMESPACE_END


#endif // TABLE_VIEW_PRIVATE_H