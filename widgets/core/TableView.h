#ifndef TABLEVIEW_H
#define TABLEVIEW_H
#include <QTableView>
#include <QPropertyAnimation>
#include <QHeaderView>

#include "ContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class TableViewPrivate;
class CUKE_EXPORT TableView : public ContextMixin<QTableView> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(TableView)
public:
    explicit TableView(QWidget *parent = nullptr);
    ~TableView() override;
};
CUKE_END_NAMESPACE(widget)

#endif // TABLEVIEW_H
