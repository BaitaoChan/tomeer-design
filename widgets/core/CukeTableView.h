#ifndef TABLEVIEW_H
#define TABLEVIEW_H
#include <QTableView>
#include <QPropertyAnimation>
#include <QHeaderView>

#include "CukeContext.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeTableViewPrivate;
class CUKE_EXPORT CukeTableView : public QTableView, public CukeContext {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeTableView)
public:
    explicit CukeTableView(QWidget *parent = nullptr);
    ~CukeTableView() override;
};
CUKE_NAMESPACE_END(pub)

#endif // TABLEVIEW_H
