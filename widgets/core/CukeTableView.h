#ifndef TABLEVIEW_H
#define TABLEVIEW_H
#include <QTableView>
#include <QPropertyAnimation>
#include <QHeaderView>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class TableViewPrivate;
class CUKE_EXPORT TableView : public QTableView {
    Q_OBJECT
    CUKE_DECLARE_DPTR(TableView)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit TableView(QWidget *parent = nullptr);
    ~TableView() override;

protected:
    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // TABLEVIEW_H
