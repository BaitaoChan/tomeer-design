#ifndef TABLEVIEW_H
#define TABLEVIEW_H
#include <QTableView>
#include <QPropertyAnimation>
#include <QHeaderView>

#include "CukeContextMixin.h"

CUKE_NAMESPACE_BEGIN(widget)
class CukeTableViewPrivate;
class CUKE_EXPORT CukeTableView : public CukeContextMixin<QTableView> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeTableView)
public:
    explicit CukeTableView(QWidget *parent = nullptr);
    ~CukeTableView() override;
};
CUKE_NAMESPACE_END(widget)

#endif // TABLEVIEW_H
