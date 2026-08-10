#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H
#include <QTableView>
#include <QPropertyAnimation>
#include <QHeaderView>

#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class TableViewPrivate;
class WIDGETS_EXPORT TableView : public QTableView {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(TableView)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit TableView(QWidget *parent = nullptr);
    ~TableView() override;

protected:
    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // TABLE_VIEW_H